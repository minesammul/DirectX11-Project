#pragma once
#include <Script.h>

class CBulletScript : public CScript
{
private:
	float		m_fSpeed;
	Vec3		direction;
	Vec3 distance;
	const float MAX_DISTANCE = 400.f;
	bool isDestroy;
	bool isEffectStart;
	CAnimation2D* effectAnimation;

public:
	CBulletScript();
	virtual ~CBulletScript();
	CLONE(CBulletScript);

public:
	virtual void start();
	virtual void update();

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void SetDirection(Vec3 direction) { this->direction = direction; }
};

