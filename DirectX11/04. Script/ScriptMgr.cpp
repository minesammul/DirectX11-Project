#include "stdafx.h"
#include "ScriptMgr.h"

#include "HilightScript.h"
#include "SSN001CameraScript.h"
#include "SSN002PlayerScript.h"
#include "SSN003CameraArmScript.h"
#include "SSN004CameraBodyScript.h"
#include "SSN005NavScript.h"
#include "SSN006WeaponEquipScript.h"
#include "SSN007MonsterScript.h"
#include "SSN008AttackBoxScript.h"
#include "SSN009HitBoxScript.h"
#include "SSN010EventQueueScript.h"
#include "SSN011PlayerUIScript.h"
#include "SSN012SkyBoxScript.h"
#include "SSN013MusicScript.h"
#include "SSN014DirectionLightScript.h"
#include "SSN015StageEventScript.h"
#include "SSN016ParticleScript.h"
#include "SSN017InOutsideScript.h"
#include "SSN018EffectScript.h"
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
	_vec.push_back(L"SSN007MonsterScript");
	_vec.push_back(L"SSN008AttackBoxScript");
	_vec.push_back(L"SSN009HitBoxScript");
	_vec.push_back(L"SSN010EventQueueScript");
	_vec.push_back(L"SSN011PlayerUIScript");
	_vec.push_back(L"SSN012SkyBoxScript");
	_vec.push_back(L"SSN013MusicScript");
	_vec.push_back(L"SSN014DirectionLightScript");
	_vec.push_back(L"SSN015StageEventScript");
	_vec.push_back(L"SSN016ParticleScript");
	_vec.push_back(L"SSN017InOutsideScript");
	_vec.push_back(L"SSN018EffectScript");
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
	if (L"SSN007MonsterScript" == _strScriptName)
		return new CSSN007MonsterScript;
	if (L"SSN008AttackBoxScript" == _strScriptName)
		return new CSSN008AttackBoxScript;
	if (L"SSN009HitBoxScript" == _strScriptName)
		return new CSSN009HitBoxScript;
	if (L"SSN010EventQueueScript" == _strScriptName)
		return new CSSN010EventQueueScript;
	if (L"SSN011PlayerUIScript" == _strScriptName)
		return new CSSN011PlayerUIScript;
	if (L"SSN012SkyBoxScript" == _strScriptName)
		return new CSSN012SkyBoxScript;
	if (L"SSN013MusicScript" == _strScriptName)
		return new CSSN013MusicScript;
	if (L"SSN014DirectionLightScript" == _strScriptName)
		return new CSSN014DirectionLightScript;
	if (L"SSN015StageEventScript" == _strScriptName)
		return new CSSN015StageEventScript;
	if (L"SSN016ParticleScript" == _strScriptName)
		return new CSSN016ParticleScript;
	if (L"SSN017InOutsideScript" == _strScriptName)
		return new CSSN017InOutsideScript;
	if (L"SSN018EffectScript" == _strScriptName)
		return new CSSN018EffectScript;
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

	case SCRIPT_TYPE::SSN007MONSTERSCRIPT:
		return L"SSN007MonsterScript";
		break;

	case SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT:
		return L"SSN008AttackBoxScript";
		break;

	case SCRIPT_TYPE::SSN009HITBOXSCRIPT:
		return L"SSN009HitBoxScript";
		break;

	case SCRIPT_TYPE::SSN010EVENTQUEUESCRIPT:
		return L"SSN010EventQueueScript";
		break;

	case SCRIPT_TYPE::SSN011PLAYERUISCRIPT:
		return L"SSN011PlayerUIScript";
		break;

	case SCRIPT_TYPE::SSN012SKYBOXSCRIPT:
		return L"SSN012SkyBoxScript";
		break;

	case SCRIPT_TYPE::SSN013MUSICSCRIPT:
		return L"SSN013MusicScript";
		break;

	case SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT:
		return L"SSN014DirectionLightScript";
		break;

	case SCRIPT_TYPE::SSN015STAGEEVENTSCRIPT:
		return L"SSN015StageEventScript";
		break;

	case SCRIPT_TYPE::SSN016PARTICLESCRIPT:
		return L"SSN016ParticleScript";
		break;

	case SCRIPT_TYPE::SSN017INOUTSIDESCRIPT:
		return L"SSN017InOutsideScript";
		break;

	case SCRIPT_TYPE::SSN018EFFECTSCRIPT:
		return L"SSN018EffectScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"TestScript";
		break;

	}
	return nullptr;
}