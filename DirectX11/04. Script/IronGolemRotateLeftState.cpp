#include "stdafx.h"
#include "IronGolemRotateLeftState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "IronGolemDieState.h"

IronGolemRotateLeftState::IronGolemRotateLeftState()
{
}


IronGolemRotateLeftState::~IronGolemRotateLeftState()
{
}

bool IronGolemRotateLeftState::CheckIdleState(CSSN007MonsterScript * monsterScript)
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

	if (degree > 10.f)
	{
		return false;
	}
	else
	{
		return true;
	}
}

IronGolemRotateLeftState * IronGolemRotateLeftState::GetInstance()
{
	static IronGolemRotateLeftState instance;
	return &instance;
}

void IronGolemRotateLeftState::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Rotate_Left", true);
}

void IronGolemRotateLeftState::Update(CSSN007MonsterScript * monsterScript)
{
	if (CheckDieState(monsterScript) == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
		return;
	}
	else if (CheckIdleState(monsterScript) == true)
	{
		IronGolemIdleState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemIdleState::GetInstance());
	}
	else
	{
		Vec3 mosnterRotate = monsterScript->Object()->Transform()->GetLocalRot();
		mosnterRotate.y -= GetRadian(monsterScript->GetMonsterRotateSpeed());
		monsterScript->Object()->Transform()->SetLocalRot(mosnterRotate);
	}

}