#include "stdafx.h"
#include "TopWallCollisionScript.h"


CTopWallCollisionScript::CTopWallCollisionScript():
	CScript((UINT)SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT)
{
}


CTopWallCollisionScript::~CTopWallCollisionScript()
{
}

void CTopWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionOn = true;

	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();
}

void CTopWallCollisionScript::OnCollision(CCollider2D* _pOther)
{
	Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
	characterPosition.y = collisionPosition.y;
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}

void CTopWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;
}
