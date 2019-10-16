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
	collisionOn = true;

	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();
}

void CLeftWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	//Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
	//characterPosition.x = collisionPosition.x;
	//Object()->GetParent()->Transform()->SetLocalPos(characterPosition);

	Vec3 characterPosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
	Vec3 characterScale = Object()->GetParent()->Collider2D()->GetFinalScale();
	characterPosition.x = _pOther->Object()->Transform()->GetLocalPos().x + (_pOther->Object()->Transform()->GetLocalScale().x / 2) + (characterScale.x / 2);
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}

void CLeftWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;

}
