#include "stdafx.h"
#include "MonsterFly.h"


MonsterFly::MonsterFly()
{
	
}


MonsterFly::~MonsterFly()
{
}

void MonsterFly::Move(CMonsterScript * monster)
{
	vector<CGameObject*> playerObject;
	CSceneMgr::GetInst()->FindGameObject(L"Player", playerObject);

	Vec3 playerPosition = playerObject[0]->Transform()->GetLocalPos();

	Vec3 monsterDirection = XMVector2Normalize(playerPosition);

	Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();
	monsterPosition.x += monsterDirection.x * FLY_SPEED*DT;
	monsterPosition.y += monsterDirection.y * FLY_SPEED*DT;

	monster->Object()->Transform()->SetLocalPos(monsterPosition);
}
