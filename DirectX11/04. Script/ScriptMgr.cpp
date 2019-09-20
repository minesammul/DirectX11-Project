#include "stdafx.h"
#include "ScriptMgr.h"

#include "BulletScript.h"
#include "HilightScript.h"
#include "MonsterScript.h"
#include "PlayerScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"BulletScript");
	_vec.push_back(L"HilightScript");
	_vec.push_back(L"MonsterScript");
	_vec.push_back(L"PlayerScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"BulletScript" == _strScriptName)
		return new CBulletScript;
	if (L"HilightScript" == _strScriptName)
		return new CHilightScript;
	if (L"MonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"PlayerScript" == _strScriptName)
		return new CPlayerScript;
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"BulletScript";
		break;

	case SCRIPT_TYPE::HILIGHTSCRIPT:
		return L"HilightScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"MonsterScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"PlayerScript";
		break;

	}
	return nullptr;
}