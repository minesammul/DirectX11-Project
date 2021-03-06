#pragma once

class CScript;
class CGameObject;

class CFunctionMgr
{
	SINGLE(CFunctionMgr);

public:
	CScript* FindScript(wstring objectName, SCRIPT_TYPE scriptType);
	CScript* FindScript(CGameObject* object, SCRIPT_TYPE scriptType);
	CGameObject* FindObject(wstring objectName);
	CGameObject* FindObjectInChildUseLayer(CGameObject* parent, wstring layerName);
	void SetAnimation(CGameObject* applyObject, wstring findAnimationName, bool isRepeat);
	float GetNowAnimationTimeRatio(CGameObject* object);
};

