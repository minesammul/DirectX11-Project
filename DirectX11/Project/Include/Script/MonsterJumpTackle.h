#pragma once
#include "MonsterAttackStrategy.h"

class MonsterJumpTackle : public MonsterAttackStrategy
{
private:
	bool firstJumping;
	bool gravityApply;

public:
	MonsterJumpTackle();
	~MonsterJumpTackle();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;
	virtual void Init();

};

