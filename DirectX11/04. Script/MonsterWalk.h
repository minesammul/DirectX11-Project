#pragma once
#include "MonsterMoveStrategy.h"

class MonsterWalk : public MonsterMoveStrategy
{
private:
	const float WALK_SPEED = 100.f;
	const float WALK_DISTANCE = 200.f;
	float nowWalkDistance;

public:
	MonsterWalk();
	~MonsterWalk();

public:
	// MonsterMoveStrategy��(��) ���� ��ӵ�
	virtual void Move(CMonsterScript * monster) override;

};

