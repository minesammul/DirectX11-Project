#pragma once
#include <Script.h>

class CRightBottomWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;

	bool collisionOn;

	const int USE_POINT_INDEX_0 = 1;
	const int USE_POINT_INDEX_1 = 3;

public:
	CRightBottomWallCollisionScript();
	~CRightBottomWallCollisionScript();

public:
	virtual void update();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetCollision(bool collision) { collisionOn = collision; }
};

