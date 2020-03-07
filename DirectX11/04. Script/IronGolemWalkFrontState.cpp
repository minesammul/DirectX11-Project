#include "stdafx.h"
#include "IronGolemWalkFrontState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "IronGolemDieState.h"

IronGolemWalkFrontState::IronGolemWalkFrontState():
	PLAYER_FIND_DISTANCE(200.f)
{
}


IronGolemWalkFrontState::~IronGolemWalkFrontState()
{
}

bool IronGolemWalkFrontState::CheckIdleState(CSSN007MonsterScript * monsterScript)
{
	Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
	Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

	float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

	if (monsterToPlayerDistance < PLAYER_FIND_DISTANCE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IronGolemWalkFrontState * IronGolemWalkFrontState::GetInstance()
{
	static IronGolemWalkFrontState instance;
	return &instance;
}

void IronGolemWalkFrontState::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Walk_Front", true);
}

void IronGolemWalkFrontState::Update(CSSN007MonsterScript * monsterScript)
{
	if (CheckDieState(monsterScript) == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
	}
	else if (CheckIdleState(monsterScript) == true)
	{
		IronGolemIdleState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemIdleState::GetInstance());
	}
	else
	{
		Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
		Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

		Vec3 monsterWalkDirection = playerPosition - monsterPosition;
		monsterWalkDirection.Normalize();

		Vec3 monsterLookAtDirection = monsterWalkDirection;
		monsterScript->Object()->Transform()->SetLookAt(monsterLookAtDirection);

		monsterPosition += monsterScript->GetMonsterMoveSpeed() * monsterWalkDirection;
		monsterScript->Object()->Transform()->SetLocalPos(monsterPosition);

		float radianValue = GetRadian(270.f);
		Vec3 monsterRoatate = monsterScript->Object()->Transform()->GetLocalRot();
		monsterRoatate.x = radianValue;
		monsterScript->Object()->Transform()->SetLocalRot(monsterRoatate);
	}
}