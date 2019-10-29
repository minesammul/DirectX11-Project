#pragma once
#include "MonsterAttackStrategy.h"

class MonsterCircleShotBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;
	const float CREATE_INTERVAL = 100.f;

public:
	MonsterCircleShotBullet();
	~MonsterCircleShotBullet();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;

};

