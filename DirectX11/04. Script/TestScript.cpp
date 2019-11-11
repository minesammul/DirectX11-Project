#include "stdafx.h"
#include "TestScript.h"


CTestScript::CTestScript() : 
	CScript((UINT)SCRIPT_TYPE::TESTSCRIPT)
{
}


CTestScript::~CTestScript()
{
}

void CTestScript::update()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_TAB)
	{

	}
}
