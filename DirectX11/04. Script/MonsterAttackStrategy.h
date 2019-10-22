#pragma once
#include "MonsterScript.h"

class MonsterAttackStrategy
{
private:
	bool isAttack;

public:
	MonsterAttackStrategy();
	virtual ~MonsterAttackStrategy();

public:
	virtual void Attack(CMonsterScript* monster) = 0;

	bool GetIsAttack(void) { return isAttack; }
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; }
};

