#include "stdafx.h"
#include "PlatformCollisionScript.h"
#include "GravityScript.h"


CPlatformCollisionScript::CPlatformCollisionScript():
	CScript((UINT)SCRIPT_TYPE::PLATFORMCOLLISIONSCRIPT)
{
}


CPlatformCollisionScript::~CPlatformCollisionScript()
{
}

void CPlatformCollisionScript::update()
{
}

void CPlatformCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	//_pOther->Object();

	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex=0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
			gravityScript->SetActiveGravity(false);
		}
	}
}
