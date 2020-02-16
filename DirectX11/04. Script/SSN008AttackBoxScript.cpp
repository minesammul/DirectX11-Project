#include "stdafx.h"
#include "SSN008AttackBoxScript.h"


CSSN008AttackBoxScript::CSSN008AttackBoxScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT)
{
}


CSSN008AttackBoxScript::~CSSN008AttackBoxScript()
{
}

void CSSN008AttackBoxScript::start()
{
	activeCollision = false;
	isAttacked = false;
}

void CSSN008AttackBoxScript::update()
{
}
