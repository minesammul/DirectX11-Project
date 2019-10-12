#include "stdafx.h"
#include "RightBottomWallCollisionScript.h"


CRightBottomWallCollisionScript::CRightBottomWallCollisionScript() : 
	CScript((UINT)SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT)
{
}


CRightBottomWallCollisionScript::~CRightBottomWallCollisionScript()
{
}

void CRightBottomWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();
}

void CRightBottomWallCollisionScript::OnCollision(CCollider2D * _pOther)
{

}
