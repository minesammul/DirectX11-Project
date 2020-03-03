#pragma once
class CFunctionMgr
{
	SINGLE(CFunctionMgr);

public:
	CScript* FindScript(wstring objectName, SCRIPT_TYPE scriptType);
};

