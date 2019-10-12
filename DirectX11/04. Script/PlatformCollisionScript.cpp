#include "stdafx.h"
#include "PlatformCollisionScript.h"
#include "GravityScript.h"
#include "PlayerActionState.h"
#include "PlayerActionStateJump.h"

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
	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();

	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLAYERSCRIPT)
		{
			CPlayerScript* playerScript = dynamic_cast<CPlayerScript*>(parentScripts[scriptIndex]);
			if (playerScript->GetActionState() == PlayerActionStateJump::GetInstance())
			{
				bool isFall = PlayerActionStateJump::GetInstance()->GetIsFall();

				if (isFall == false)
				{
					return;
				}
			}
		}
	}

	for (int scriptIndex=0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
			gravityScript->SetActiveGravity(false);
		}
	}
}

void CPlatformCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
			gravityScript->SetActiveGravity(true);
		}
	}
}
