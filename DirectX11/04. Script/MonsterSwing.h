#pragma once
#include "MonsterAttackStrategy.h"
class MonsterSwing : public MonsterAttackStrategy
{
public:
	MonsterSwing();
	~MonsterSwing();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;

};

