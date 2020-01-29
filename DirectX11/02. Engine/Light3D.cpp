#include "stdafx.h"
#include "Light3D.h"

#include "ResMgr.h"
#include "RenderMgr.h"
#include "Transform.h"
#include "MRT.h"
#include "Camera.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
	, m_pMtrl(nullptr)
	, m_iIdx(-1)
{
	// 광원 시점으로 카메라 관리
	m_pCamObj = new CGameObject;
	m_pCamObj->AddComponent(new CTransform);
	m_pCamObj->AddComponent(new CCamera);

	// 광원이 관리하는 카메라는 렌더매니저에 등록되면 안된다.
	m_pCamObj->Camera()->SetRegisterOnOff(false);
	m_pCamObj->Camera()->CheckLayerAll(); // 모든 레이어를 찍는다(shadow map)
}

CLight3D::CLight3D(const CLight3D & _light)
	: CComponent(_light)
	, m_tInfo(_light.m_tInfo)
	, m_pMtrl(_light.m_pMtrl)
	, m_pMesh(_light.m_pMesh)
	, m_iIdx(-1)
	, m_pCamObj(nullptr)
{
	m_pCamObj = _light.m_pCamObj->Clone();
}

CLight3D::~CLight3D()
{
	SAFE_DELETE(m_pCamObj);
}

void CLight3D::finalupdate()
{
	m_tInfo.vPos = Transform()->GetWorldPos();
	m_iIdx = CRenderMgr::GetInst()->RegisterLight3D(this);

	// 광원 관리 카메라도 광원과 같은 Transform 정보를 가지게 한다.
	*m_pCamObj->Transform() = *Transform();
	m_pCamObj->finalupdate(); // 렌더매니저에 등록하지 않게 해두었다.

}

void CLight3D::render()
{
	m_pMtrl->SetData(SHADER_PARAM::INT_0, &m_iIdx);

	CCamera* pMainCam = CRenderMgr::GetInst()->GetMainCam();
	if (nullptr == pMainCam)
	{
		return;
	}

	g_transform.matView = pMainCam->GetViewMat();
	g_transform.matProj = pMainCam->GetProjMat();
	g_transform.matViewInv = pMainCam->GetViewInvMat();

	Transform()->UpdateData();

	// Directional Light 인 경우
	if (m_tInfo.iType == (UINT)LIGHT_TYPE::DIRECTIONAL)
	{
		// 광원 시점 ShadowMap 깊이정보 텍스쳐
		CResPtr<CTexture> pShadowMapTex = CResMgr::GetInst()->FindRes<CTexture>(L"ShadowmapTargetTex");
		m_pMtrl->SetData(SHADER_PARAM::TEX_2, &pShadowMapTex);

		// 광원으로 투영시키기 위한 광원 View, Proj 행렬
		Matrix matVP = m_pCamObj->Camera()->GetViewMat() * m_pCamObj->Camera()->GetProjMat();
		m_pMtrl->SetData(SHADER_PARAM::MAT_0, &matVP);

		// MainCamera InvViewMatrix
		Matrix matInvView = CRenderMgr::GetInst()->GetMainCam()->GetViewInvMat();
		m_pMtrl->SetData(SHADER_PARAM::MAT_1, &matInvView);
	}

	m_pMtrl->UpdateData();

	m_pMesh->SetLayout(m_pMtrl->GetShader());
	m_pMesh->render(0);
}

void CLight3D::render_shadowmap()
{
	if (m_tInfo.iType != (UINT)LIGHT_TYPE::DIRECTIONAL)
		return;

	CRenderMgr::GetInst()->GetMRT(MRT_TYPE::SHADOWMAP)->OMSet();

	m_pCamObj->Camera()->SortShadowGameObject();
	m_pCamObj->Camera()->render_shadowmap();
}

void CLight3D::SetLightType(LIGHT_TYPE _eType)
{
	m_tInfo.iType = (UINT)_eType;

	if ((UINT)LIGHT_TYPE::DIRECTIONAL == m_tInfo.iType)
	{
		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"DirLightMtrl");
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");

		m_pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		m_pCamObj->Camera()->SetWidth(7680.f);
		m_pCamObj->Camera()->SetHeight(7680.f);

	}
	else if ((UINT)LIGHT_TYPE::POINT == m_tInfo.iType)
	{
		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PointLightMtrl");
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
	}
	else
	{

	}
}

void CLight3D::SetLightDir(const Vec3 & _vLightDir)
{
	m_tInfo.vDir = _vLightDir;
	m_tInfo.vDir.Normalize();

	Transform()->SetLookAt(Vec3(m_tInfo.vDir.x, m_tInfo.vDir.y, m_tInfo.vDir.z));
}

void CLight3D::SetLightRange(float _fRange)
{
	m_tInfo.fRange = _fRange;
	Transform()->SetLocalScale(Vec3(_fRange, _fRange, _fRange));
}

void CLight3D::SaveToScene(FILE * _pFile)
{
	fwrite(&m_tInfo.vDiff, sizeof(Vec4), 1, _pFile);
	fwrite(&m_tInfo.vSpec, sizeof(Vec4), 1, _pFile);
	fwrite(&m_tInfo.vAmb, sizeof(Vec4), 1, _pFile);
	fwrite(&m_tInfo.vPos, sizeof(Vec4), 1, _pFile);
	fwrite(&m_tInfo.vDir, sizeof(Vec4), 1, _pFile);
	fwrite(&m_tInfo.iType, sizeof(UINT), 1, _pFile);
	fwrite(&m_tInfo.fRange, sizeof(float), 1, _pFile);
	fwrite(&m_tInfo.fAngle, sizeof(float), 1, _pFile);

	bool bMesh = true;
	bool bMtrl = true;

	if (nullptr == m_pMesh)
		bMesh = false;
	if (nullptr == m_pMtrl)
		bMtrl = false;

	fwrite(&bMesh, 1, 1, _pFile);
	if (bMesh)
	{
		SaveWString(m_pMesh->GetName().c_str(), _pFile);
		SaveWString(m_pMesh->GetPath().c_str(), _pFile);
	}

	fwrite(&bMtrl, 1, 1, _pFile);
	if (bMtrl)
	{
		SaveWString(m_pMtrl->GetName().c_str(), _pFile);
		SaveWString(m_pMtrl->GetPath().c_str(), _pFile);
	}
}

void CLight3D::LoadFromScene(FILE * _pFile)
{
	fread(&m_tInfo.vDiff, sizeof(Vec4), 1, _pFile);
	fread(&m_tInfo.vSpec, sizeof(Vec4), 1, _pFile);
	fread(&m_tInfo.vAmb, sizeof(Vec4), 1, _pFile);
	fread(&m_tInfo.vPos, sizeof(Vec4), 1, _pFile);
	fread(&m_tInfo.vDir, sizeof(Vec4), 1, _pFile);
	fread(&m_tInfo.iType, sizeof(UINT), 1, _pFile);
	fread(&m_tInfo.fRange, sizeof(float), 1, _pFile);
	fread(&m_tInfo.fAngle, sizeof(float), 1, _pFile);

	bool bMesh = true;
	bool bMtrl = true;

	wstring strKey, strPath;

	fread(&bMesh, 1, 1, _pFile);
	if (bMesh)
	{
		strKey = LoadWString(_pFile);
		strPath = LoadWString(_pFile);

		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(strKey);
		if (nullptr == m_pMesh)
		{
			CResMgr::GetInst()->Load<CMesh>(strKey, strPath);
		}
	}

	fread(&bMtrl, 1, 1, _pFile);
	if (bMtrl)
	{
		strKey = LoadWString(_pFile);
		strPath = LoadWString(_pFile);

		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strKey);
		if (nullptr == m_pMtrl)
		{
			CResMgr::GetInst()->Load<CMaterial>(strKey, strPath);
		}
	}
}
