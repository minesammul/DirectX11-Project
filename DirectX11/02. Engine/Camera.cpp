#include "stdafx.h"
#include "Camera.h"

#include "Transform.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "RenderMgr.h"

#include "GameObject.h"
#include "MeshRender.h"
#include "Material.h"
#include "Shader.h"
#include "KeyMgr.h"
#include "Device.h"
#include "Collider2D.h"
#include "Animator2D.h"
#include "Animator3D.h"
#include "Animation2D.h"
#include "ResMgr.h"

CCamera::CCamera()
	: m_eType(PROJ_TYPE::PERSPECTIVE)
	, m_fScale(1.f)
	, m_fFOV(XM_PI / 4.f)
	, m_fNear(1.f)
	, m_fFar(100000.f)
	, m_iLayerCheck(0)
	, m_iCamOrder(0)
	, CComponent(COMPONENT_TYPE::CAMERA)
	, m_fWidth(0.f)
	, m_fHeight(0.f)
	, m_bRegister(true)
{	
	tResolution tRes = CRenderMgr::GetInst()->GetResolution();
	m_fWidth = tRes.fWidth;
	m_fHeight = tRes.fHeight;
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
}

void CCamera::finalupdate()
{
	Vec3 vPos = Transform()->GetLocalPos();

	// View 행렬 만들기
	m_matView = XMMatrixIdentity();
	m_matView._41 = -vPos.x;	
	m_matView._42 = -vPos.y;
	m_matView._43 = -vPos.z;
	
	Vec3 vRight = Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
	Vec3 vUp = Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
	Vec3 vFront = Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);

	// 우, 상, 전 행렬을 단위행렬(기저벡터) 로 만들수 있는 회전행렬이 바로 뷰스페이스 회전행렬
	// 기저벡터 행렬이 단위행렬이기 때문에, 뷰스페이스 회전행렬은 우, 상, 전 행렬의 역행렬이다.
	// 우, 상, 전 으로 만들어진 행렬은 직교행렬이기 때문에 전치행렬이 곧 역행렬

	Matrix matViewRot;
	matViewRot = Matrix::Identity;
	matViewRot._11 = vRight.x; matViewRot._12 = vUp.x; matViewRot._13 = vFront.x;
	matViewRot._21 = vRight.y; matViewRot._22 = vUp.y; matViewRot._23 = vFront.y;
	matViewRot._31 = vRight.z; matViewRot._32 = vUp.z; matViewRot._33 = vFront.z;


	m_matView *= matViewRot;
	m_matViewInv = XMMatrixInverse(nullptr, m_matView); // View 역행렬

	// Projection 행렬 만들기	
	if (m_eType == PROJ_TYPE::PERSPECTIVE)
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, m_fWidth / m_fHeight, m_fNear, m_fFar);
	else
		m_matProj = XMMatrixOrthographicLH(m_fWidth * m_fScale, m_fHeight * m_fScale, m_fNear, m_fFar);

	CalRay();

	// 카메라를 현재 Scene 에 등록
	if (m_bRegister)
		CRenderMgr::GetInst()->RegisterCamera(this);
}

void CCamera::render_deferred()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	g_transform.matView = m_matView;
	g_transform.matViewInv = XMMatrixInverse(nullptr, m_matView);
	g_transform.matProj = m_matProj;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == pCurScene->GetLayer(i))
			continue;

		if (IsValiedLayer(i))
		{
			const vector<CGameObject*>& vecObj = pCurScene->GetLayer(i)->GetAllObject();

			for (size_t i = 0; i < vecObj.size(); ++i)
			{
				if (nullptr == vecObj[i]->MeshRender())
				{
					continue;
				}

				// Animation 관련 정보 업데이트
				if (vecObj[i]->Animator2D())
					vecObj[i]->Animator2D()->UpdateData();
				else
					CAnimation2D::ClearRegister();

				if (vecObj[i]->Animator3D())
					vecObj[i]->Animator3D()->UpdateData();

				vecObj[i]->Transform()->UpdateData();

				// 재질 수 만큼 반복돌면서 렌더링
				UINT iMtrlCount = vecObj[i]->MeshRender()->GetMaterialCount();
				for (UINT j = 0; j < iMtrlCount; ++j)
				{
					if (nullptr == vecObj[i]->MeshRender()->GetSharedMaterial(j)
						|| nullptr == vecObj[i]->MeshRender()->GetSharedMaterial(j)->GetShader())
						continue;

					if (vecObj[i]->MeshRender()->GetSharedMaterial(j)->GetShader()->IsDeferred())
					{
						vecObj[i]->MeshRender()->render(j);
					}
				}

				if (vecObj[i]->Collider2D())
				{
					vecObj[i]->Collider2D()->render();
				}

			}
		}
	}
}

void CCamera::render_forward()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == pCurScene->GetLayer(i))
			continue;

		if (IsValiedLayer(i))
		{
			const vector<CGameObject*>& vecObj = pCurScene->GetLayer(i)->GetAllObject();

			for (size_t i = 0; i < vecObj.size(); ++i)
			{
				if (nullptr == vecObj[i]->MeshRender())
					continue;

				UINT iMtrlCount = vecObj[i]->MeshRender()->GetMaterialCount();
				for (UINT j = 0; j < iMtrlCount; ++j)
				{
					if (nullptr == vecObj[i]->MeshRender()->GetSharedMaterial(j)
						|| nullptr == vecObj[i]->MeshRender()->GetSharedMaterial(j)->GetShader())
						continue;

					if (!vecObj[i]->MeshRender()->GetSharedMaterial(j)->GetShader()->IsDeferred())
					{
						vecObj[i]->render();
					}
				}
			}
		}
	}
}

const tRay & CCamera::GetRay()
{
	CalRay();

	return m_tRay;
}

void CCamera::CheckLayer(UINT _iLayerIdx)
{
	UINT iCheck = 1 << _iLayerIdx;
	if (m_iLayerCheck & iCheck)
		m_iLayerCheck &= ~iCheck;
	else
		m_iLayerCheck |= iCheck;
}

void CCamera::CalRay()
{
	POINT ptMousePos = CKeyMgr::GetInst()->GetMousePos();

	D3D11_VIEWPORT tVP = {};
	UINT iSize = 1;
	CONTEXT->RSGetViewports(&iSize, &tVP);

	if (iSize == 0)
	{
		tResolution res = CRenderMgr::GetInst()->GetResolution();
		tVP.Width = res.fWidth;
		tVP.Height = res.fHeight;
		tVP.MinDepth = 1.f;
		tVP.MaxDepth = 1.f;
		tVP.TopLeftX = 0.f;
		tVP.TopLeftY = 0.f;
	}

	m_tRay.vStart = Transform()->GetWorldPos();
	m_tRay.vDir.x = ((((ptMousePos.x - tVP.TopLeftX) * 2.f / tVP.Width) - 1.f) - m_matProj._31) / m_matProj._11;
	m_tRay.vDir.y = (-(((ptMousePos.y - tVP.TopLeftY) * 2.f / tVP.Height) - 1.f) - m_matProj._32) / m_matProj._22;
	m_tRay.vDir.z = 1.f;

	m_tRay.vDir = XMVector3TransformNormal(m_tRay.vDir, m_matViewInv);
	m_tRay.vDir.Normalize();
}

void CCamera::SaveToScene(FILE * _pFile)
{
	fwrite(&m_eType, sizeof(UINT), 1, _pFile);
	fwrite(&m_fScale, sizeof(float), 1, _pFile);
	fwrite(&m_fFOV, sizeof(float), 1, _pFile);
	fwrite(&m_fNear, sizeof(float), 1, _pFile);
	fwrite(&m_fFar, sizeof(float), 1, _pFile);
	fwrite(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
	fwrite(&m_iCamOrder, sizeof(UINT), 1, _pFile);
}

void CCamera::LoadFromScene(FILE * _pFile)
{
	fread(&m_eType, sizeof(UINT), 1, _pFile);
	fread(&m_fScale, sizeof(float), 1, _pFile);
	fread(&m_fFOV, sizeof(float), 1, _pFile);
	fread(&m_fNear, sizeof(float), 1, _pFile);
	fread(&m_fFar, sizeof(float), 1, _pFile);
	fread(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
	fread(&m_iCamOrder, sizeof(UINT), 1, _pFile);
}

void CCamera::render_shadowmap()
{
	// 뷰행렬과 투영행렬을 광원시점 카메라의 것으로 대체해둠
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;
	g_transform.matViewInv = m_matViewInv;

	for (UINT i = 0; i < m_vecShadowObj.size(); ++i)
	{
		CResPtr<CTexture> pBoneTex = nullptr;
		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ShadowMapMtrl");
		if (m_vecShadowObj[i]->Animator3D())
		{
			m_vecShadowObj[i]->Animator3D()->UpdateData();
			CResPtr<CTexture> pBoneTex = m_vecShadowObj[i]->Animator3D()->GetBornTex();
			pMtrl->SetData(SHADER_PARAM::TEX_7, &pBoneTex);
		}
		else
		{
			pMtrl->SetData(SHADER_PARAM::TEX_7, &pBoneTex);
		}

		m_vecShadowObj[i]->MeshRender()->render_shadowmap();
	}
}


void CCamera::SortShadowGameObject()
{
	m_vecShadowObj.clear();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = nullptr;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		pLayer = pCurScene->GetLayer(i);
		if (nullptr == pLayer || !(m_iLayerCheck & (1 << i)))
			continue;

		const vector<CGameObject*>& vecObj = pLayer->GetAllObject();

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			// MeshRender 가 없거나, Material 을 참조하지 않는 경우
			if (vecObj[j]->MeshRender() == nullptr
				|| vecObj[j]->MeshRender()->GetSharedMaterial() == nullptr
				|| vecObj[j]->MeshRender()->GetSharedMaterial()->GetShader() == nullptr)
			{
				continue;
			}

			// Frustum Check
			//if (!m_frustum.CheckShpere(vecObj[j]))
			//{
			//	continue;
			//}

			if (vecObj[j]->MeshRender()->IsShadowObj())
			{
				m_vecShadowObj.push_back(vecObj[j]);
			}
		}
	}
}