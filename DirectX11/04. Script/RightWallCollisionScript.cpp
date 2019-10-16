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
	collisionOn = true;
	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();
}

void CRightWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	Vec3 characterPosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
	Vec3 characterScale = Object()->GetParent()->Collider2D()->GetFinalScale();
	characterPosition.x = _pOther->Object()->Transform()->GetLocalPos().x - (_pOther->Object()->Transform()->GetLocalScale().x / 2) - (characterScale.x / 2);
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}

void CRightWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;
}
