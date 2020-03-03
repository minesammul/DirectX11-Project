#pragma once
#include <Script.h>

class CSSN005NavScript : public CScript
{
private:
	bool mIsNavCollision;
	map<UINT, bool> mNavObjectCollisionCheck;

	Vec3 mBeforePosition;

public:
	CSSN005NavScript();
	~CSSN005NavScript();

public:
	virtual void start();
	virtual void update();

	virtual void OnCollision(CCollider3D* _pOther);
	virtual void OnCollisionExit(CCollider3D* _pOther);

	bool GetNavCollision() { return mIsNavCollision; }

	Vec3 GetBeforePosition() { return mBeforePosition; }
};

