#include "stdafx.h"
#include "IronGolemIdleState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemWalkFrontState.h"
#include "IronGolemAttack1State.h"
#include "IronGolemAttack3State.h"
#include "IronGolemRotateLeftState.h"
#include "IronGolemRotateRightState.h"
#include "IronGolemDieState.h"
#include "SSN008AttackBoxScript.h"

IronGolemIdleState::IronGolemIdleState() :
	PLAYER_FIND_DISTANCE(1500.f),
	PLAYER_ATTACK_DISTANCE(500.f),
	PLAYER_LOOKAT_ROTATE_DEGREE(20.f)
{
}


IronGolemIdleState::~IronGolemIdleState()
{
}

bool IronGolemIdleState::CheckWalkState(CSSN007MonsterScript * monsterScript)
{
	Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
	Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

	float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

	if (PLAYER_ATTACK_DISTANCE < monsterToPlayerDistance && monsterToPlayerDistance < PLAYER_FIND_DISTANCE)
	{
		if (CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object()) >= 0.9f)
		{
			return true;
		}
	}

	return false;
}

bool IronGolemIdleState::CheckAttackState(CSSN007MonsterScript * monsterScript)
{
	Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
	Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

	float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

	if (monsterToPlayerDistance < PLAYER_ATTACK_DISTANCE)
	{
		if (CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object()) >= 0.9f)
		{
			return true;
		}
	}

	return false;
}

IronGolemIdleState * IronGolemIdleState::GetInstance()
{
	static IronGolemIdleState instance;
	return &instance;
}

void IronGolemIdleState::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Idle", true);
	monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	monsterScript->GetAttackBoxScript()->SetAttackted(false);
}

void IronGolemIdleState::Update(CSSN007MonsterScript * monsterScript)
{
	if (CheckDieState(monsterScript) == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
	}
	else if (CheckRotateLeftState(monsterScript, PLAYER_LOOKAT_ROTATE_DEGREE) == true)
	{
		IronGolemRotateLeftState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemRotateLeftState::GetInstance());
	}
	else if (CheckRotateRightState(monsterScript, PLAYER_LOOKAT_ROTATE_DEGREE) == true)
	{
		IronGolemRotateRightState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemRotateRightState::GetInstance());
	}
	else if (CheckWalkState(monsterScript) == true)
	{
		IronGolemWalkFrontState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemWalkFrontState::GetInstance());
	}
	else if (CheckAttackState(monsterScript) == true)
	{
		srand(time(0));
		int attackType = rand() % 10;

		if (attackType < 5)
		{
			IronGolemAttack1State::GetInstance()->Init(monsterScript);
			monsterScript->SetState(IronGolemAttack1State::GetInstance());
		}
		else
		{
			IronGolemAttack3State::GetInstance()->Init(monsterScript);
			monsterScript->SetState(IronGolemAttack3State::GetInstance());
		}
	}
}

