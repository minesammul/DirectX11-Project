#pragma once
#include <Script.h>

class CSSN009HitBoxScript : public CScript
{
private:
	//bool isCollision;


public:
	CSSN009HitBoxScript();
	~CSSN009HitBoxScript();

public:
	virtual void OnCollision(CCollider3D* _pOther);

	//bool GetCollision() { return isCollision; }
	//void SetCollision(bool collision) { isCollision = collision; }
};

