#pragma once
#include <Script.h>

class CGravityScript : public CScript
{
private:
	const float GRAVITY_VALUE = 0.98f;
	float nowGravityValue;

	bool activeGravity;


public:
	CGravityScript();
	~CGravityScript();

public:
	CLONE(CGravityScript);

public:
	virtual void update();
	void SetActiveGravity(bool gravity) { activeGravity = gravity; }
};

