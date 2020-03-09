#pragma once
#include <Script.h>

class CSSN014DirectionLightScript : public CScript
{
private:
	Vec3 mPlayerBeforePosition;
	CGameObject* mPlayer;

public:
	CSSN014DirectionLightScript();
	~CSSN014DirectionLightScript();

public:
	virtual void start();
	virtual void update();
};

