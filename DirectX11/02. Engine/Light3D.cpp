#include "stdafx.h"
#include "Light3D.h"

#include "ResMgr.h"
#include "RenderMgr.h"
#include "Transform.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
	, m_pMtrl(nullptr)
	, m_iIdx(-1)
{
}

CLight3D::~CLight3D()
{
}

void CLight3D::finalupdate()
{
	m_tInfo.vPos = Transform()->GetWorldPos();
	m_iIdx = CRenderMgr::GetInst()->RegisterLight3D(this);
}

void CLight3D::render()
{

	m_pMtrl->SetData(SHADER_PARAM::INT_0, &m_iIdx);

	Transform()->UpdateData();

	m_pMtrl->UpdateData();

	m_pMesh->SetLayout(m_pMtrl->GetShader());
	m_pMesh->render();
}

void CLight3D::SetLightType(LIGHT_TYPE _eType)
{
	m_tInfo.iType = (UINT)_eType;

	if ((UINT)LIGHT_TYPE::DIRECTIONAL == m_tInfo.iType)
	{
		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"DirLightMtrl");
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	}
	else if ((UINT)LIGHT_TYPE::POINT == m_tInfo.iType)
	{
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PointLightMtrl");
	}
	else
	{

	}
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
