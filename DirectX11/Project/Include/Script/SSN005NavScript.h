#pragma once
#include <Script.h>

class CSSN005NavScript : public CScript
{
private:
	bool isNavCollision;
	map<UINT, bool> navObjectCollisionCheck;

	Vec3 beforePosition;

public:
	CSSN005NavScript();
	~CSSN005NavScript();

public:
	virtual void start();
	virtual void update();
	virtual void OnCollision(CCollider3D* _pOther);
	virtual void OnCollisionExit(CCollider3D* _pOther);

	bool GetNavCollision() { return isNavCollision; }

	Vec3 GetBeforePosition() { return beforePosition; }
};

