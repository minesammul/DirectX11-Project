#include "stdafx.h"
#include "SaveLoadMgr.h"

#include <ResMgr.h>
#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>
#include <GameObject.h>


CSaveLoadMgr::CSaveLoadMgr(){}
CSaveLoadMgr::~CSaveLoadMgr(){}

void CSaveLoadMgr::SaveScene(const wstring& _strPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strPath.c_str(), L"wb");

	// ���ҽ� ����
	SaveResource(pFile);

	// Scene ����

	fclose(pFile);
}

void CSaveLoadMgr::SaveResource(FILE* _pFile)
{
	INT i = 0;
	for (; i < (UINT)RES_TYPE::END; ++i)
	{
		// ���̴��� ����� ������ ���� �� �ε����� �ʴ´�.(Engine �ڵ忡�� ���� �����ص�)
		if (i == (UINT)RES_TYPE::SHADER)
			continue;

		const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources((RES_TYPE)i);

		// ���ҽ� Ÿ��
		fwrite(&i, sizeof(UINT), 1, _pFile);

		// �ش� ���ҽ� ����
		UINT iResCount = mapRes.size();
		fwrite(&iResCount, sizeof(UINT), 1, _pFile);

		// ���ҽ� ����
		for (const auto& pair : mapRes)
		{
			pair.second->SaveToScene(_pFile);
		}
	}	

	// ������ End ���� (���� �˸�)
	fwrite(&i, sizeof(UINT), 1, _pFile);
}


void CSaveLoadMgr::LoadScene(const wstring & _strPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strPath.c_str(), L"rb");

	// ���ҽ� �ҷ�����
	LoadResource(pFile);

	// Scene �ҷ�����

	fclose(pFile);	
}

void CSaveLoadMgr::LoadResource(FILE * _pFile)
{
	UINT iResType = (UINT)RES_TYPE::END;
	UINT iResCount = 0;
	while(true)
	{
		// ���ҽ� Ÿ��
		fread(&iResType, sizeof(UINT), 1, _pFile);

		// ���ҽ��� �� �о���.
		if ((UINT)RES_TYPE::END == iResType)
			break;

		// ���ҽ� ����		
		fread(&iResCount, sizeof(UINT), 1, _pFile);

		CResource* pResource = nullptr;
		bool bRet = true;

		for (UINT i = 0; i < iResCount; ++i)
		{
			switch ((RES_TYPE)iResType)
			{
			case RES_TYPE::MATERIAL:
				pResource = new CMaterial;
				break;
			case RES_TYPE::PREFAB:
				pResource = new CPrefab;
				break;
			case RES_TYPE::MESH:
				pResource = new CMesh;						
				break;
			case RES_TYPE::TEXTURE:
				pResource = new CTexture;
				break;
			case RES_TYPE::SOUND:
				// pResource = new CSound;
				break;			
			}

			bRet = pResource->LoadFromScene(_pFile);
			if (false == bRet)
				delete pResource;

			CResMgr::GetInst()->AddRes((RES_TYPE)i, pResource);
		}
	}
}
