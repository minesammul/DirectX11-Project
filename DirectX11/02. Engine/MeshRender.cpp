#include "stdafx.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Transform.h"

#include "Collider2D.h"
#include "Collider3D.h"
#include "Animator2D.h"
#include "Animation2D.h"
#include "Animator3D.h"
#include "ResMgr.h"
#include "Camera.h"

CMeshRender::CMeshRender()
	: m_pMesh(nullptr)
	, m_bShadow(true)
	, CComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

CResPtr<CMaterial> CMeshRender::GetCloneMaterial(UINT _iSubset)
{
	if (nullptr == m_vecMtrl[_iSubset])
		return nullptr;

	m_vecMtrl[_iSubset] = m_vecMtrl[_iSubset]->Clone();

	CResMgr::GetInst()->AddCloneRes(m_vecMtrl[_iSubset]);

	return m_vecMtrl[_iSubset];
}

void CMeshRender::update()
{
}

void CMeshRender::render()
{	
	Transform()->UpdateData();

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		CAnimation2D::ClearRegister();
	}

	if (Animator3D())
	{
		Animator3D()->UpdateData();
	}

	for (UINT i = 0; i < m_vecMtrl.size(); ++i)
	{
		if (nullptr == m_vecMtrl[i] || nullptr == m_vecMtrl[i]->GetShader())
			continue;

		// Graphics Pipeline 단계에서 사용할 정점의 Layout 정보 전달	
		m_pMesh->SetLayout(m_vecMtrl[i]->GetShader());
		m_vecMtrl[i]->UpdateData();
		m_pMesh->render(i);
		CTexture::ClearAllRegister();
	}

	// Collider2D 가 있으면 그려준다.
	if (nullptr != Collider2D())
		Collider2D()->render();

	// Collider3D 가 있으면 그려준다.
	if (nullptr != Collider3D())
		Collider3D()->render();
}	

void CMeshRender::render(UINT _iMtrl)
{
	m_pMesh->SetLayout(m_vecMtrl[_iMtrl]->GetShader());
	m_vecMtrl[_iMtrl]->UpdateData();
	m_pMesh->render(_iMtrl);

	// Collider3D 가 있으면 그려준다.
	if (nullptr != Collider3D())
		Collider3D()->render();

	CTexture::ClearAllRegister();
}

void CMeshRender::render_shadowmap()
{
	CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ShadowMapMtrl");

	Transform()->UpdateData();

	for (UINT i = 0; i < m_vecMtrl.size(); ++i)
	{
		pMtrl->UpdateData();
		m_pMesh->SetLayout(pMtrl->GetShader());
		m_pMesh->render(i);
	}
}

void CMeshRender::SetMesh(CResPtr<CMesh> _pMesh)
{
	m_pMesh = _pMesh;
	UINT iSubsetCount = m_pMesh->GetSubsetCount();

	if (m_vecMtrl.size() < iSubsetCount)
	{
		m_vecMtrl.resize(iSubsetCount);
	}
	else if (m_vecMtrl.size() > iSubsetCount)
	{
		vector<CResPtr<CMaterial>> vecTemp;
		vecTemp.resize(iSubsetCount);
		m_vecMtrl.swap(vecTemp);
	}
}

ULONG64 CMeshRender::GetInstID(UINT _iMtrlIdx)
{
	if (m_pMesh == NULL || m_vecMtrl[_iMtrlIdx] == NULL)
		return 0;

	uInstID id{ m_pMesh->GetID(), (WORD)m_vecMtrl[_iMtrlIdx]->GetID(), (WORD)_iMtrlIdx };
	return id.llID;
}

void CMeshRender::SaveToScene(FILE * _pFile)
{
	fwrite(&m_bShadow, 1, 1, _pFile);

	bool bMesh = true, bMtrl = true;

	if (nullptr == m_pMesh)
		bMesh = false;
	if (m_vecMtrl.empty())
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
		UINT iSize = m_vecMtrl.size();
		fwrite(&iSize, sizeof(UINT), 1, _pFile);

		UINT i = 0;
		for (; i < m_vecMtrl.size(); ++i)
		{
			if (nullptr == m_vecMtrl[i])
				continue;

			fwrite(&i, sizeof(UINT), 1, _pFile);
			SaveWString(m_vecMtrl[i]->GetName().c_str(), _pFile);
			SaveWString(m_vecMtrl[i]->GetPath().c_str(), _pFile);
		}

		i = -1; // 마감 용도
		fwrite(&i, sizeof(UINT), 1, _pFile);
	}
}

void CMeshRender::LoadFromScene(FILE * _pFile)
{
	fread(&m_bShadow, 1, 1, _pFile);


	bool bMesh = true, bMtrl = true;

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
		UINT iSize = 0;
		fread(&iSize, sizeof(UINT), 1, _pFile);
		m_vecMtrl.resize(iSize);

		UINT iIdx = 0;
		fread(&iIdx, sizeof(UINT), 1, _pFile);

		while (iIdx != -1)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			if (strPath.empty() == false)
			{
				SetMaterial(CResMgr::GetInst()->Load<CMaterial>(strPath, strPath), iIdx);
			}
			else
			{
				SetMaterial(CResMgr::GetInst()->Load<CMaterial>(strKey, strPath), iIdx);
			}

			fread(&iIdx, sizeof(UINT), 1, _pFile);
		}
	}
}

