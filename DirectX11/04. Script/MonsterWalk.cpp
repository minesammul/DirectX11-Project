#include "stdafx.h"
#include "MonsterWalk.h"


MonsterWalk::MonsterWalk()
{
	nowWalkDistance = 0;
	SetIsMove(true);
}


MonsterWalk::~MonsterWalk()
{
}

void MonsterWalk::Move(CMonsterScript * monster)
{

	Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

	Vec3 monsterDirection = Vec3(1.f, 0.f, 0.f);

	monsterPosition.x += monsterDirection.x*WALK_SPEED*DT;

	monster->Object()->Transform()->SetLocalPos(monsterPosition);

	nowWalkDistance += monsterDirection.x*WALK_SPEED*DT;
	if (nowWalkDistance > WALK_DISTANCE)
	{
		nowWalkDistance = 0.f;
		SetIsMove(false);
	}

}
