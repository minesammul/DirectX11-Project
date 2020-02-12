#include "stdafx.h"
#include "ScriptMgr.h"

#include "HilightScript.h"
#include "SSN001CameraScript.h"
#include "SSN002PlayerScript.h"
#include "SSN003CameraArmScript.h"
#include "SSN004CameraBodyScript.h"
#include "SSN005NavScript.h"
#include "SSN006WeaponEquipScript.h"
#include "TestScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"HilightScript");
	_vec.push_back(L"SSN001CameraScript");
	_vec.push_back(L"SSN002PlayerScript");
	_vec.push_back(L"SSN003CameraArmScript");
	_vec.push_back(L"SSN004CameraBodyScript");
	_vec.push_back(L"SSN005NavScript");
	_vec.push_back(L"SSN006WeaponEquipScript");
	_vec.push_back(L"TestScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"HilightScript" == _strScriptName)
		return new CHilightScript;
	if (L"SSN001CameraScript" == _strScriptName)
		return new CSSN001CameraScript;
	if (L"SSN002PlayerScript" == _strScriptName)
		return new CSSN002PlayerScript;
	if (L"SSN003CameraArmScript" == _strScriptName)
		return new CSSN003CameraArmScript;
	if (L"SSN004CameraBodyScript" == _strScriptName)
		return new CSSN004CameraBodyScript;
	if (L"SSN005NavScript" == _strScriptName)
		return new CSSN005NavScript;
	if (L"SSN006WeaponEquipScript" == _strScriptName)
		return new CSSN006WeaponEquipScript;
	if (L"TestScript" == _strScriptName)
		return new CTestScript;
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::HILIGHTSCRIPT:
		return L"HilightScript";
		break;

	case SCRIPT_TYPE::SSN001CAMERASCRIPT:
		return L"SSN001CameraScript";
		break;

	case SCRIPT_TYPE::SSN002PLAYERSCRIPT:
		return L"SSN002PlayerScript";
		break;

	case SCRIPT_TYPE::SSN003CAMERAARMSCRIPT:
		return L"SSN003CameraArmScript";
		break;

	case SCRIPT_TYPE::SSN004CAMERABODYSCRIPT:
		return L"SSN004CameraBodyScript";
		break;

	case SCRIPT_TYPE::SSN005NAVSCRIPT:
		return L"SSN005NavScript";
		break;

	case SCRIPT_TYPE::SSN006WEAPONEQUIPSCRIPT:
		return L"SSN006WeaponEquipScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"TestScript";
		break;

	}
	return nullptr;
}