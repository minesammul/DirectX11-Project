#pragma once
#include "Script.h"

class BulletScript : public Script
{
private:
	float m_fSpeed;

public:
	BulletScript();
	virtual ~BulletScript();

public:
	virtual void Update();

public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
};

