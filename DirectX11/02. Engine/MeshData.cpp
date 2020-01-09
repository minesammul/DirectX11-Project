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
	int meshCount = loader.GetContainerCount();
	CMeshData* pMeshData = new CMeshData;
	for (int meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		//���⿡ ������� loader�� �ε��� ����
		CMesh* pMesh = CMesh::CreateFromContainer(loader, meshIndex);

		// Animation �� �ִ� Mesh ��� BoneTexture �����α�
		if (pMesh->IsAnimMesh())
		{
			wstring strBoneTex = _strPath;
			strBoneTex += to_wstring(meshIndex);
			strBoneTex += L"BoneTex";

			CResPtr<CTexture> pBoneTex =
				CResMgr::GetInst()->CreateTexture(strBoneTex
					, pMesh->GetBones()->size() * 4, 1
					, D3D11_BIND_SHADER_RESOURCE
					, D3D11_USAGE_DYNAMIC
					, DXGI_FORMAT_R32G32B32A32_FLOAT);

			pMesh->SetBoneTex(pBoneTex);
		}

		// ResMgr �� �޽� ���

		wstring strMeshName = L"Mesh\\";
		strMeshName += CPathMgr::GetFileName(strFullPath.c_str());
		strMeshName += to_wstring(meshIndex);
		strMeshName += L".mesh";

		pMesh->SetName(strMeshName);
		pMesh->SetPath(strMeshName);

		CResMgr::GetInst()->AddRes<CMesh>(pMesh->GetName(), pMesh);

		vector<CResPtr<CMaterial>> vecMtrl;

		// ���׸��� ��������
		for (UINT i = 0; i < loader.GetContainer(meshIndex).vecMtrl.size(); ++i)
		{
			// ����ó�� (material �̸��� �Է� �ȵǾ����� ���� �ִ�.)
			CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(loader.GetContainer(meshIndex).vecMtrl[i].strMtrlName);
			vecMtrl.push_back(pMtrl);
		}

		pMeshData->m_vecMesh.push_back(pMesh);
		pMeshData->m_vecMtrl.push_back(vecMtrl);
	}
	

	return pMeshData;
}


void CMeshData::Load(const wstring & _strFilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	// Mesh Load
	int meshCount = 0;
	fread(&meshCount, sizeof(UINT), 1, pFile);
	m_vecMesh.resize(meshCount);
	m_vecMtrl.resize(meshCount);

	for (int meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		wstring strMeshKey, strMeshPath;
		strMeshKey = LoadWString(pFile);
		strMeshPath = LoadWString(pFile);

		CResPtr<CMesh> inputData = CResMgr::GetInst()->Load<CMesh>(strMeshKey, strMeshPath);
		m_vecMesh[meshIndex] = inputData;

		// material ���� �б�
		UINT iMtrlCount = 0;
		fread(&iMtrlCount, sizeof(UINT), 1, pFile);

		m_vecMtrl[meshIndex].resize(iMtrlCount);

		for (UINT i = 0; i < iMtrlCount; ++i)
		{
			UINT idx = -1;
			fread(&idx, 4, 1, pFile);
			if (idx == -1)
				break;

			wstring strKey = LoadWString(pFile);
			wstring strPath = LoadWString(pFile);

			CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->Load<CMaterial>(strPath, strPath);
			m_vecMtrl[meshIndex][i] = pMtrl;
		}
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
	int meshCount = m_vecMesh.size();
	fwrite(&meshCount, sizeof(UINT), 1, pFile);

	for (int meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		m_vecMesh[meshIndex]->Save();

		// Mesh Key ����	
		// Mesh Data ����
		SaveWString(m_vecMesh[meshIndex]->GetName().c_str(), pFile);
		SaveWString(m_vecMesh[meshIndex]->GetPath().c_str(), pFile);

		// material ���� ����
		UINT iMtrlCount = m_vecMesh[meshIndex]->GetSubsetCount();
		iMtrlCount = m_vecMtrl[meshIndex].size();
		fwrite(&iMtrlCount, sizeof(UINT), 1, pFile);

		UINT i = 0;
		for (; i < iMtrlCount; ++i)
		{
			if (nullptr == m_vecMtrl[meshIndex][i])
				continue;

			// Material �� ���Ϸ� ����
			m_vecMtrl[meshIndex][i]->Save();

			// Material �ε���, Key, Path ����
			fwrite(&i, sizeof(UINT), 1, pFile);
			SaveWString(m_vecMtrl[meshIndex][i]->GetName().c_str(), pFile);
			SaveWString(m_vecMtrl[meshIndex][i]->GetPath().c_str(), pFile);
		}
	}
	

	int endValue = -1; // ���� ��
	fwrite(&endValue, sizeof(UINT), 1, pFile);

	fclose(pFile);
}

bool CMeshData::LoadFromScene(FILE * _pFile)
{
	SetName(LoadWString(_pFile));

	// ���
	wstring strPath = LoadWString(_pFile);

	return false;
}

CGameObject * CMeshData::Instantiate()
{
	// Mesh
	// Material

	CGameObject* pRootObj = new CGameObject;
	pRootObj->AddComponent(new CTransform);
	pRootObj->AddComponent(new CMeshRender);

	int meshCount = m_vecMesh.size();

	for (int meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		CGameObject* pNewObj = new CGameObject;
		pNewObj->AddComponent(new CTransform);
		pNewObj->AddComponent(new CMeshRender);

		wstring meshName = m_vecMesh[meshIndex]->GetName();
		pNewObj->SetName(meshName);

		pNewObj->MeshRender()->SetMesh(m_vecMesh[meshIndex]);

		for (UINT i = 0; i < m_vecMtrl[meshIndex].size(); ++i)
		{
			pNewObj->MeshRender()->SetMaterial(m_vecMtrl[meshIndex][i], i);
		}

		if (true == m_vecMesh[meshIndex]->IsAnimMesh())
		{
			CAnimator3D* pAnimator = new CAnimator3D;
			pNewObj->AddComponent(pAnimator);

			pAnimator->SetBones(m_vecMesh[meshIndex]->GetBones());
			pAnimator->SetAnimClip(m_vecMesh[meshIndex]->GetAnimClip());
			pAnimator->SetBoneTex(m_vecMesh[meshIndex]->GetBoneTex());
		}


		pNewObj->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		pRootObj->AddChild(pNewObj);
	}

	

	return pRootObj;
}

