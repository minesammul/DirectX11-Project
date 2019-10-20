#include "stdafx.h"
#include "MonsterDash.h"


MonsterDash::MonsterDash()
{
	nowMoveDistance = 0.f;
	SetIsMove(true);
}


MonsterDash::~MonsterDash()
{
}

void MonsterDash::Move(CMonsterScript * monster)
{
	if (GetIsMove() == true)
	{
		Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

		Vec3 monsterDashDirection = Vec3(1.f, 0.f, 0.f);

		monsterPosition.x += monsterDashDirection.x*300.f*DT;

		nowMoveDistance += monsterDashDirection.x*300.f*DT;

		monster->Object()->Transform()->SetLocalPos(monsterPosition);

		if (nowMoveDistance > MOVE_DISTACNE)
		{
			nowMoveDistance = 0.f;
			SetIsMove(false);
		}
		else
		{
			SetIsMove(true);
		}
	}
}
