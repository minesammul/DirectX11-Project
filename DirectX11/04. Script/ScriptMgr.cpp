#include "stdafx.h"
#include "ScriptMgr.h"

#include "HilightScript.h"
#include "SSN001CameraScript.h"
#include "TestScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"HilightScript");
	_vec.push_back(L"SSN001CameraScript");
	_vec.push_back(L"TestScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"HilightScript" == _strScriptName)
		return new CHilightScript;
	if (L"SSN001CameraScript" == _strScriptName)
		return new CSSN001CameraScript;
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

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"TestScript";
		break;

	}
	return nullptr;
}