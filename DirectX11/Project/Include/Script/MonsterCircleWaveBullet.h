#pragma once
#include "MonsterAttackStrategy.h"

class MonsterCircleWaveBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;

public:
	MonsterCircleWaveBullet();
	~MonsterCircleWaveBullet();

public:
	// MonsterAttackStrategy��(��) ���� ��ӵ�
	virtual void Attack(CMonsterScript * monster) override;

};

