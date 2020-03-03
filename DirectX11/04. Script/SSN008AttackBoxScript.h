#pragma once
#include <Script.h>

class CSSN008AttackBoxScript : public CScript
{
private:
	bool mActiveCollision;
	bool mIsAttacked;

public:
	CSSN008AttackBoxScript();
	~CSSN008AttackBoxScript();

public:
	virtual void start();
	virtual void update();

	bool GetActiveCollision() { return mActiveCollision; }
	void SetActiveCollision(bool active) { mActiveCollision = active; }

	bool GetAttackted() { return mIsAttacked; }
	void SetAttackted(bool attacked) { mIsAttacked = attacked; }
};

