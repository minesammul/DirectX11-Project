#pragma once

#include <vector>
#include <string>

enum class SCRIPT_TYPE
{
	BULLETSCRIPT,
	GRAVITYSCRIPT,
	HILIGHTSCRIPT,
	MONSTERSCRIPT,
	PLAYERSCRIPT,
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
