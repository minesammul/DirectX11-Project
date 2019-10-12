#pragma once
#include <Script.h>

class CRightBottomWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;

public:
	CRightBottomWallCollisionScript();
	~CRightBottomWallCollisionScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
};

