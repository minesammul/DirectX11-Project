#pragma once
#include "MonsterAttackStrategy.h"

class MonsterTrace : public MonsterAttackStrategy
{
private:
	const float MAX_TRACE_DISTANCE = 300.f;
	float nowTraceDistance;
	
	const float TRACE_SPEED = 300.f;

public:
	MonsterTrace();
	~MonsterTrace();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;

};

