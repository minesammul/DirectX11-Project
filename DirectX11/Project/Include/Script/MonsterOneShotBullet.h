#pragma once
#include "MonsterAttackStrategy.h"

class MonsterOneShotBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;

public:
	MonsterOneShotBullet();
	~MonsterOneShotBullet();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;

};

