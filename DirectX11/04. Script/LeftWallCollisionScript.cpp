#include "stdafx.h"
#include "LeftWallCollisionScript.h"


CLeftWallCollisionScript::CLeftWallCollisionScript():
	CScript((UINT)SCRIPT_TYPE::LEFTWALLCOLLISIONSCRIPT)
{
}


CLeftWallCollisionScript::~CLeftWallCollisionScript()
{
}

void CLeftWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();
}

void CLeftWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
	characterPosition.x = collisionPosition.x;
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}
