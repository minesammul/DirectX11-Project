#include "stdafx.h"
#include "RightWallCollisionScript.h"


CRightWallCollisionScript::CRightWallCollisionScript():
	CScript((UINT)SCRIPT_TYPE::RIGHTWALLCOLLISIONSCRIPT)
{
}


CRightWallCollisionScript::~CRightWallCollisionScript()
{
}

void CRightWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();
}

void CRightWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
	characterPosition.x = collisionPosition.x;
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}
