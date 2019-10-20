#pragma once
#include "MonsterMoveStrategy.h"

class MonsterDash : public MonsterMoveStrategy
{
private:
	const float MOVE_DISTACNE = 300.f;
	float nowMoveDistance;

public:
	MonsterDash();
	~MonsterDash();

public:
	// MonsterMoveStrategy��(��) ���� ��ӵ�
	virtual void Move(CMonsterScript * monster) override;

};

