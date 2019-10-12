#pragma once
#include "Script.h"
class CTopWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;

public:
	CTopWallCollisionScript();
	~CTopWallCollisionScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
};

