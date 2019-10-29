#pragma once
#include "MonsterMoveStrategy.h"

class MonsterFly : public MonsterMoveStrategy
{
private:
	const float FLY_SPEED = 200.f;
	const float MAX_FLY_DISTACNE = 200.f;
	Vec3 nowFlyDistance;

public:
	MonsterFly();
	~MonsterFly();

public:
	// MonsterMoveStrategy��(��) ���� ��ӵ�
	virtual void Move(CMonsterScript * monster) override;

};

