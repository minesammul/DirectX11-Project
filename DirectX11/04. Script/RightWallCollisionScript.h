#pragma once
#include <Script.h>

class CRightWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;

public:
	CRightWallCollisionScript();
	~CRightWallCollisionScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
};

