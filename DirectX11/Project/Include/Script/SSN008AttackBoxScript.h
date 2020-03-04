#pragma once
#include <Script.h>

class CSSN008AttackBoxScript : public CScript
{
private:
	bool mIsActiveCollision;
	bool mIsAttacked;

public:
	CSSN008AttackBoxScript();
	~CSSN008AttackBoxScript();

public:
	virtual void start();

	bool GetActiveCollision() { return mIsActiveCollision; }
	void SetActiveCollision(bool active) { mIsActiveCollision = active; }

	bool GetAttackted() { return mIsAttacked; }
	void SetAttackted(bool attacked) { mIsAttacked = attacked; }
};

