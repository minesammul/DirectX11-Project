#pragma once
#include "MonsterMoveStrategy.h"

class MonsterFly : public MonsterMoveStrategy
{
private:
	const float FLY_SPEED = 200.f;

public:
	MonsterFly();
	~MonsterFly();

public:
	// MonsterMoveStrategy을(를) 통해 상속됨
	virtual void Move(CMonsterScript * monster) override;

};

