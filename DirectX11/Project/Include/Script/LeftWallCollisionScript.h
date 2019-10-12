#pragma once
#include <Script.h>

class CLeftWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;

public:
	CLeftWallCollisionScript();
	~CLeftWallCollisionScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
};

