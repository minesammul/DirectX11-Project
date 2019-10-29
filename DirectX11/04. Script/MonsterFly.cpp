#include "stdafx.h"
#include "MonsterFly.h"


MonsterFly::MonsterFly()
{
	nowFlyDistance = Vec3(0.f, 0.f, 0.f);
}


MonsterFly::~MonsterFly()
{
}

void MonsterFly::Move(CMonsterScript * monster)
{
	monster->SetMonsterDirectionImage();
	
	Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();
	Vec3 monsterDirection = monster->GetMonsterDirection();

	monsterPosition.x += monsterDirection.x * FLY_SPEED*DT;
	monsterPosition.y += monsterDirection.y * FLY_SPEED*DT;

	monster->Object()->Transform()->SetLocalPos(monsterPosition);


	nowFlyDistance.x += monsterDirection.x * FLY_SPEED*DT;
	nowFlyDistance.y += monsterDirection.y * FLY_SPEED*DT;
	
	Vec3 distance = XMVector2Length(nowFlyDistance);
	if (distance.x > MAX_FLY_DISTACNE)
	{
		SetIsMove(false);
	}
}
