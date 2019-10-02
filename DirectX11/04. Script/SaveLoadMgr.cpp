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

	// 리소스 저장
	SaveResource(pFile);

	// Scene 저장

	fclose(pFile);
}

void CSaveLoadMgr::SaveResource(FILE* _pFile)
{
	INT i = 0;
	for (; i < (UINT)RES_TYPE::END; ++i)
	{
		// 쉐이더는 설계상 문제로 저장 및 로드하지 않는다.(Engine 코드에서 전부 생성해둠)
		if (i == (UINT)RES_TYPE::SHADER)
			continue;

		const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources((RES_TYPE)i);

		// 리소스 타입
		fwrite(&i, sizeof(UINT), 1, _pFile);

		// 해당 리소스 개수
		UINT iResCount = mapRes.size();
		fwrite(&iResCount, sizeof(UINT), 1, _pFile);

		// 리소스 정보
		for (const auto& pair : mapRes)
		{
			pair.second->SaveToScene(_pFile);
		}
	}	

	// 리스소 End 정보 (끝을 알림)
	fwrite(&i, sizeof(UINT), 1, _pFile);
}


void CSaveLoadMgr::LoadScene(const wstring & _strPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strPath.c_str(), L"rb");

	// 리소스 불러오기
	LoadResource(pFile);

	// Scene 불러오기

	fclose(pFile);	
}

void CSaveLoadMgr::LoadResource(FILE * _pFile)
{
	UINT iResType = (UINT)RES_TYPE::END;
	UINT iResCount = 0;
	while(true)
	{
		// 리소스 타입
		fread(&iResType, sizeof(UINT), 1, _pFile);

		// 리소스를 다 읽었다.
		if ((UINT)RES_TYPE::END == iResType)
			break;

		// 리소스 개수		
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
