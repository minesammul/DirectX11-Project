#include "stdafx.h"
#include "BottomWallCollisionScript.h"
#include "RightBottomWallCollisionScript.h"
#include "LeftBottomWallCollisionScript.h"
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
	collisionOn = true;

	vector<CGameObject*> brotherObject = Object()->GetParent()->GetChild();
	for (int brotherIndex = 0; brotherIndex < brotherObject.size(); brotherIndex++)
	{
		vector<CScript*> brotherScripts;
		brotherScripts = brotherObject[brotherIndex]->GetScripts();

		for (int scriptIndex = 0; scriptIndex < brotherScripts.size(); scriptIndex++)
		{
			if (brotherScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT)
			{
				CRightBottomWallCollisionScript* rightBottomWallCollisionScript = dynamic_cast<CRightBottomWallCollisionScript*>(brotherScripts[scriptIndex]);
				rightBottomWallCollisionScript->SetCollision(false);
			}

			if (brotherScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::LEFTBOTTOMWALLCOLLISIONSCRIPT)
			{
				CLeftBottomWallCollisionScript* leftBottomWallCollisionScript = dynamic_cast<CLeftBottomWallCollisionScript*>(brotherScripts[scriptIndex]);
				leftBottomWallCollisionScript->SetCollision(false);
			}
		}
	}
}

void CBottomWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	if (collisionOn == true)
	{
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

		Vec3 characterPosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
		Vec3 characterScale = Object()->GetParent()->Collider2D()->GetFinalScale();
		characterPosition.y = _pOther->Object()->Transform()->GetLocalPos().y + (_pOther->Object()->Transform()->GetLocalScale().y/2) + (characterScale.y/2) - 2.f;
		Object()->GetParent()->Transform()->SetLocalPos(characterPosition);

		collisionPosition = characterPosition;
	}

}

void CBottomWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;
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
