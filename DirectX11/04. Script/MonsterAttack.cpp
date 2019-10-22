#include "stdafx.h"
#include "MonsterAttack.h"

#include "MonsterAttackStrategy.h"
#include "MonsterCircleWaveBullet.h"

MonsterAttack::MonsterAttack()
{
	circleWaveBullet = new MonsterCircleWaveBullet;

	attackStrategy = nullptr;
}


MonsterAttack::~MonsterAttack()
{
	if (circleWaveBullet != nullptr)
	{
		delete circleWaveBullet;
	}
}

void MonsterAttack::Init()
{
	if (GetMonster()->Object()->GetName().compare(L"Banshee") == 0)
	{
		attackStrategy = circleWaveBullet;
	}
}

void MonsterAttack::Update(CMonsterScript * monster)
{
	attackStrategy->Attack(monster);
}
