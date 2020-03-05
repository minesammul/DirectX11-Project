#include "stdafx.h"
#include "FunctionMgr.h"

#include <GameObject.h>
#include <Scene.h>
#include <SceneMgr.h>
#include <Script.h>
#include <Animator3D.h>

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
		assert(false && L"Is not find want object");
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

void CFunctionMgr::SetAnimation(CGameObject * applyObject, wstring findAnimationName, bool isRepeat)
{
	for (int index = 0; index < applyObject->GetChild().size(); index++)
	{
		if (applyObject->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		int findAnimationIndex = -1;

		if (applyObject->GetChild()[index]->Animator3D()->FindAnimClipIndex(findAnimationName, findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		applyObject->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		applyObject->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
		applyObject->GetChild()[index]->Animator3D()->SetRepeat(isRepeat);
	}
}

float CFunctionMgr::GetNowAnimationTimeRatio(CGameObject * object)
{
	float curRatioAnimTime = 1.f;

	for (int index = 0; index < object->GetChild().size(); index++)
	{
		if (object->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (object->GetChild()[index]->Animator3D()->IsDoneAnimation() == false)
		{
			float ratioAnimationTime = object->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
			if (ratioAnimationTime < curRatioAnimTime)
			{
				curRatioAnimTime = ratioAnimationTime;
			}
		}
	}

	return curRatioAnimTime;
}
