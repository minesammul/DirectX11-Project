#include "stdafx.h"
#include "FunctionMgr.h"

#include <GameObject.h>
#include <Scene.h>
#include <SceneMgr.h>
#include <Script.h>

CFunctionMgr::CFunctionMgr()
{
}


CFunctionMgr::~CFunctionMgr()
{
}

CScript * CFunctionMgr::FindScript(wstring objectName, SCRIPT_TYPE scriptType)
{
	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(objectName, findObject);

	CScript* findScript = nullptr;
	for (int index = 0; index < findObject[0]->GetScripts().size(); index++)
	{
		if (findObject[0]->GetScripts()[index]->GetScriptType() == (UINT)scriptType)
		{
			findScript = findObject[0]->GetScripts()[index];
			break;
		}
	}

	return findScript;
}

CGameObject * CFunctionMgr::FindObject(wstring objectName)
{
	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->FindGameObject(objectName, findObject);

	if (findObject.empty() == true)
	{
		assert(false && L"CameraScript is not find want object");
	}

	return findObject[0];
}

CGameObject * CFunctionMgr::FindObjectInChildUseLayer(CGameObject* parent, wstring layerName)
{
	CGameObject* findObject = nullptr;
	for (int index = 0; index < parent->GetChild().size(); index++)
	{
		CLayer* findLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(layerName);
		if (parent->GetChild()[index]->GetLayerIdx() == findLayer->GetLayerIdx())
		{
			findObject = parent->GetChild()[index];
			break;
		}
	}

	return findObject;
}
