#pragma once

#include <vector>
#include <string>

enum class SCRIPT_TYPE
{
	HILIGHTSCRIPT,
	SSN001CAMERASCRIPT,
	SSN002PLAYERSCRIPT,
	SSN003CAMERAARMSCRIPT,
	SSN004CAMERABODYSCRIPT,
	SSN005NAVSCRIPT,
	SSN006WEAPONEQUIPSCRIPT,
	SSN007MONSTERSCRIPT,
	SSN008ATTACKBOXSCRIPT,
	SSN009HITBOXSCRIPT,
	SSN010EVENTQUEUESCRIPT,
	SSN011PLAYERUISCRIPT,
	TESTSCRIPT,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
