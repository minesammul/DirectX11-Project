#pragma once
#include "MonsterComponent.h"

class MonsterAttackStrategy;
class MonsterCircleWaveBullet;

class MonsterAttack : public MonsterComponent
{
private:
	MonsterAttackStrategy* attackStrategy;
	MonsterCircleWaveBullet* circleWaveBullet;

public:
	MonsterAttack();
	~MonsterAttack();

public:
	// MonsterComponent을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update(CMonsterScript * monster) override;

	MonsterAttackStrategy* GetAttackStrategy(void) { return attackStrategy; }
	void SetAttackStrategy(MonsterAttackStrategy* attackStrategy) { this->attackStrategy = attackStrategy; }

};

