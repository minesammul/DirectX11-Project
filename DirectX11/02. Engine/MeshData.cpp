#include "stdafx.h"
#include "MeshData.h"

#include "PathMgr.h"
#include "Mesh.h"
#include "ResMgr.h"
#include "Material.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Animator3D.h"
#include "GameObject.h"

CMeshData::CMeshData()
	: CResource(RES_TYPE::MESHDATA)
{
}

CMeshData::~CMeshData()
{
}

CMeshData * CMeshData::LoadFromFBX(const wstring& _strPath)
{
	wstring strFullPath = CPathMgr::GetResPath();
	strFullPath += _strPath;

	CFBXLoader loader;
	loader.init();
	loader.LoadFbx(strFullPath);

	// �޽� ��������
	CMesh* pMesh = CMesh::CreateFromContainer(loader);

	// Animation �� �ִ� Mesh ��� BoneTexture �����α�
	//if (pMesh->IsAnimMesh())
	//{
	//	wstring strBoneTex = _strPath;
	//	strBoneTex += L"BoneTex";
	//
	//	CResPtr<CTexture> pBoneTex =
	//		CResMgr::GetInst()->CreateTexture(strBoneTex
	//			, pMesh->GetBones()->size() * 4, 1
	//			, D3D11_BIND_SHADER_RESOURCE
	//			, DXGI_FORMAT_R32G32B32A32_FLOAT
	//			, D3D11_USAGE_DYNAMIC);
	//
	//	pMesh->SetBoneTex(pBoneTex);
	//}	

	// ResMgr �� �޽� ���

	wstring strMeshName = L"Mesh\\";
	strMeshName += CPathMgr::GetFileName(strFullPath.c_str());
	strMeshName += L".mesh";

	pMesh->SetName(strMeshName);
	pMesh->SetPath(strMeshName);

	CResMgr::GetInst()->AddRes<CMesh>(pMesh->GetName(), pMesh);

	vector<CResPtr<CMaterial>> vecMtrl;

	// ���׸��� ��������
	for (UINT i = 0; i < loader.GetContainer(0).vecMtrl.size(); ++i)
	{
		// ����ó�� (material �̸��� �Է� �ȵǾ����� ���� �ִ�.)
		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(loader.GetContainer(0).vecMtrl[i].strMtrlName);
		vecMtrl.push_back(pMtrl);
	}

	CMeshData* pMeshData = new CMeshData;
	pMeshData->m_pMesh = pMesh;
	pMeshData->m_vecMtrl = vecMtrl;

	return pMeshData;
}


void CMeshData::Load(const wstring & _strFilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	// Mesh Load
	wstring strMeshKey, strMeshPath;
	strMeshKey = LoadWString(pFile);
	strMeshPath = LoadWString(pFile);
	m_pMesh = CResMgr::GetInst()->Load<CMesh>(strMeshKey, strMeshPath);

	// material ���� �б�
	UINT iMtrlCount = 0;
	fread(&iMtrlCount, sizeof(UINT), 1, pFile);
		
	m_vecMtrl.resize(iMtrlCount);

	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		UINT idx = -1;
		fread(&idx, 4, 1, pFile);
		if (idx == -1)
			break;
		
		wstring strKey = LoadWString(pFile);
		wstring strPath = LoadWString(pFile);

		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->Load<CMaterial>(strKey, strPath);
		m_vecMtrl[i] = pMtrl;
	}

	fclose(pFile);
}

void CMeshData::Save()
{
	wstring strFileName = CPathMgr::GetResPath();
	strFileName += GetName();

	FILE* pFile = nullptr;
	errno_t err = _wfopen_s(&pFile, strFileName.c_str(), L"wb");

	// Mesh �� ���Ϸ� ����
	m_pMesh->Save();
	
	// Mesh Key ����	
	// Mesh Data ����
	SaveWString(m_pMesh->GetName().c_str(), pFile);
	SaveWString(m_pMesh->GetPath().c_str(), pFile);

	// material ���� ����
	UINT iMtrlCount = m_pMesh->GetSubsetCount();
	iMtrlCount = m_vecMtrl.size();	
	fwrite(&iMtrlCount, sizeof(UINT), 1, pFile);

	UINT i = 0;
	for (; i < iMtrlCount; ++i)
	{
		if (nullptr == m_vecMtrl[i])
			continue;

		// Material �� ���Ϸ� ����
		m_vecMtrl[i]->Save();

		// Material �ε���, Key, Path ����
		fwrite(&i, sizeof(UINT), 1, pFile);
		SaveWString(m_vecMtrl[i]->GetName().c_str(), pFile);
		SaveWString(m_vecMtrl[i]->GetPath().c_str(), pFile);
	}

	i = -1; // ���� ��
	fwrite(&i, sizeof(UINT), 1, pFile);

	fclose(pFile);
}

CGameObject * CMeshData::Instantiate()
{
	// Mesh
	// Material

	CGameObject* pNewObj = new CGameObject;	
	pNewObj->AddComponent(new CTransform);
	pNewObj->AddComponent(new CMeshRender);

	pNewObj->MeshRender()->SetMesh(m_pMesh);
	
	for (UINT i = 0; i < m_vecMtrl.size(); ++i)
	{
		pNewObj->MeshRender()->SetMaterial(m_vecMtrl[i], i);
	}

	//if (false == m_pMesh->IsAnimMesh())
	//	return pNewObj;	
	//
	//CAnimator3D* pAnimator = new CAnimator3D;
	//pNewObj->AddComponent(pAnimator);
	//
	//pAnimator->SetBones(m_pMesh->GetBones());
	//pAnimator->SetAnimClip(m_pMesh->GetAnimClip());
	//pAnimator->SetBoneTex(m_pMesh->GetBoneTex());

	return pNewObj;
}
