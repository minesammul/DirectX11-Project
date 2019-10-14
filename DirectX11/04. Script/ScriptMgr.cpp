#include "stdafx.h"
#include "ScriptMgr.h"

#include "BottomWallCollisionScript.h"
#include "BulletScript.h"
#include "GravityScript.h"
#include "HilightScript.h"
#include "LeftBottomWallCollisionScript.h"
#include "LeftWallCollisionScript.h"
#include "MonsterScript.h"
#include "PlatformCollisionScript.h"
#include "PlayerScript.h"
#include "RightBottomWallCollisionScript.h"
#include "RightWallCollisionScript.h"
#include "TileMapScript.h"
#include "TileScript.h"
#include "TopWallCollisionScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"BottomWallCollisionScript");
	_vec.push_back(L"BulletScript");
	_vec.push_back(L"GravityScript");
	_vec.push_back(L"HilightScript");
	_vec.push_back(L"LeftBottomWallCollisionScript");
	_vec.push_back(L"LeftWallCollisionScript");
	_vec.push_back(L"MonsterScript");
	_vec.push_back(L"PlatformCollisionScript");
	_vec.push_back(L"PlayerScript");
	_vec.push_back(L"RightBottomWallCollisionScript");
	_vec.push_back(L"RightWallCollisionScript");
	_vec.push_back(L"TileMapScript");
	_vec.push_back(L"TileScript");
	_vec.push_back(L"TopWallCollisionScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"BottomWallCollisionScript" == _strScriptName)
		return new CBottomWallCollisionScript;
	if (L"BulletScript" == _strScriptName)
		return new CBulletScript;
	if (L"GravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"HilightScript" == _strScriptName)
		return new CHilightScript;
	if (L"LeftBottomWallCollisionScript" == _strScriptName)
		return new CLeftBottomWallCollisionScript;
	if (L"LeftWallCollisionScript" == _strScriptName)
		return new CLeftWallCollisionScript;
	if (L"MonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"PlatformCollisionScript" == _strScriptName)
		return new CPlatformCollisionScript;
	if (L"PlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"RightBottomWallCollisionScript" == _strScriptName)
		return new CRightBottomWallCollisionScript;
	if (L"RightWallCollisionScript" == _strScriptName)
		return new CRightWallCollisionScript;
	if (L"TileMapScript" == _strScriptName)
		return new CTileMapScript;
	if (L"TileScript" == _strScriptName)
		return new CTileScript;
	if (L"TopWallCollisionScript" == _strScriptName)
		return new CTopWallCollisionScript;
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT:
		return L"BottomWallCollisionScript";
		break;

	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"BulletScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"GravityScript";
		break;

	case SCRIPT_TYPE::HILIGHTSCRIPT:
		return L"HilightScript";
		break;

	case SCRIPT_TYPE::LEFTBOTTOMWALLCOLLISIONSCRIPT:
		return L"LeftBottomWallCollisionScript";
		break;

	case SCRIPT_TYPE::LEFTWALLCOLLISIONSCRIPT:
		return L"LeftWallCollisionScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"MonsterScript";
		break;

	case SCRIPT_TYPE::PLATFORMCOLLISIONSCRIPT:
		return L"PlatformCollisionScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"PlayerScript";
		break;

	case SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT:
		return L"RightBottomWallCollisionScript";
		break;

	case SCRIPT_TYPE::RIGHTWALLCOLLISIONSCRIPT:
		return L"RightWallCollisionScript";
		break;

	case SCRIPT_TYPE::TILEMAPSCRIPT:
		return L"TileMapScript";
		break;

	case SCRIPT_TYPE::TILESCRIPT:
		return L"TileScript";
		break;

	case SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT:
		return L"TopWallCollisionScript";
		break;

	}
	return nullptr;
}