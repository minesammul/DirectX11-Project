#include "stdafx.h"
#include "BottomWallCollisionScript.h"
#include "GravityScript.h"


CBottomWallCollisionScript::CBottomWallCollisionScript():
	CScript((UINT)SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT)
{
}


CBottomWallCollisionScript::~CBottomWallCollisionScript()
{
}

void CBottomWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();

	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();

	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
			gravityScript->SetActiveGravity(false);
		}
	}
}

void CBottomWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
	characterPosition.y = collisionPosition.y;
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}

void CBottomWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
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
