#pragma once
#include "MonsterAttackStrategy.h"

class MonsterThreeShotBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;


public:
	MonsterThreeShotBullet();
	~MonsterThreeShotBullet();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;

};

