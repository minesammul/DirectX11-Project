#pragma once
#include "Object.h"

struct TGoalPosition
{
	float x;
	float y;
};

class Bullet :	public Object
{
private:
	bool m_bFire;
	TGoalPosition m_tGoal;

public:
	Bullet();
	~Bullet();

	void Update() override;
	TObject CreateObject() override;

	void SetGoalPosition(float x, float y)
	{
		m_tGoal.x = x;
		m_tGoal.y = y;
	}

	void BulletFire();

	bool IsFire()
	{
		return m_bFire;
	}

	void SetFire(bool fire)
	{
		m_bFire = fire;
	}
};

