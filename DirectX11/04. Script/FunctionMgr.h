#pragma once

class CScript;
class CGameObject;

class CFunctionMgr
{
	SINGLE(CFunctionMgr);

public:
	CScript* FindScript(wstring objectName, SCRIPT_TYPE scriptType);
	CGameObject* FindObject(wstring objectName);
	CGameObject* FindObjectInChildUseLayer(CGameObject* parent, wstring layerName);
};

