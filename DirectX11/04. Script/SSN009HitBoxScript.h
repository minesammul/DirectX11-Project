#pragma once
#include <Script.h>

class CSSN009HitBoxScript : public CScript
{
public:
	CSSN009HitBoxScript();
	~CSSN009HitBoxScript();

public:
	virtual void OnCollision(CCollider3D* _pOther);
};

