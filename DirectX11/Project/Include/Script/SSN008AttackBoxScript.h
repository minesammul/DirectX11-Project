#pragma once
#include <Script.h>

class CSSN008AttackBoxScript : public CScript
{
private:
	bool activeCollision;
	bool isAttacked;

public:
	CSSN008AttackBoxScript();
	~CSSN008AttackBoxScript();

public:
	virtual void start();
	virtual void update();

	bool GetActiveCollision() { return activeCollision; }
	void SetActiveCollision(bool active) { activeCollision = active; }

	bool GetAttackted() { return isAttacked; }
	void SetAttackted(bool attacked) { isAttacked = attacked; }
};

