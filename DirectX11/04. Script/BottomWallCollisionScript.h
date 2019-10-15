#pragma once
#include <Script.h>

class CBottomWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;
	bool collisionOn;

public:
	CBottomWallCollisionScript();
	~CBottomWallCollisionScript();
	CLONE(CBottomWallCollisionScript);
public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);
	void SetCollision(bool collision) { collisionOn = collision; }
};

