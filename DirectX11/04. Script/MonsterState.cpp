#include "stdafx.h"
#include "MonsterState.h"

#include "SSN007MonsterScript.h"
#include "SSN008AttackBoxScript.h"

MonsterState::MonsterState()
{
}


MonsterState::~MonsterState()
{
}

bool MonsterState::CheckDieState(CSSN007MonsterScript * monsterScript)
{
	return monsterScript->GetDead();
}

bool MonsterState::CheckIdleState(CSSN007MonsterScript * monsterScript)
{
	return false;
}

bool MonsterState::CheckRotateLeftState(CSSN007MonsterScript * monsterScript, float rotateStartRadian)
{
	Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
	Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

	Vec3 monsterToPlayerVector = playerPosition - monsterPosition;
	monsterToPlayerVector.Normalize();

	Vec3 monsterFrontVector = monsterScript->Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
	monsterFrontVector *= -1.f;
	monsterFrontVector.Normalize();

	float dotValue = monsterFrontVector.Dot(monsterToPlayerVector);
	float radian = acosf(dotValue);
	float degree = XMConvertToDegrees(radian);

	if (degree > rotateStartRadian)
	{
		Vec3 crossValue = monsterFrontVector.Cross(monsterToPlayerVector);

		if (crossValue.y <= 0.f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool MonsterState::CheckRotateRightState(CSSN007MonsterScript * monsterScript, float rotateStartRadian)
{
	Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
	Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

	Vec3 monsterToPlayerVector = playerPosition - monsterPosition;
	monsterToPlayerVector.Normalize();

	Vec3 monsterFrontVector = monsterScript->Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
	monsterFrontVector *= -1.f;
	monsterFrontVector.Normalize();

	float dotValue = monsterFrontVector.Dot(monsterToPlayerVector);
	float radian = acosf(dotValue);
	float degree = XMConvertToDegrees(radian);

	if (degree > rotateStartRadian)
	{
		Vec3 crossValue = monsterFrontVector.Cross(monsterToPlayerVector);

		if (crossValue.y > 0.f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void MonsterState::SetActiveAttackCollision(CSSN007MonsterScript * monsterScript, float startActiveTimeRatio, float endActiveTimeRatio)
{
	float curAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object());
	if (startActiveTimeRatio <= curAnimationTimeRatio && curAnimationTimeRatio <= endActiveTimeRatio)
	{
		monsterScript->GetAttackBoxScript()->SetActiveCollision(true);
	}
	else
	{
		monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	}
}
