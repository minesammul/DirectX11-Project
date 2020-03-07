#include "stdafx.h"
#include "IronGolemAttack1State.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "SSN008AttackBoxScript.h"
#include "IronGolemDieState.h"

IronGolemAttack1State::IronGolemAttack1State()
{
}


IronGolemAttack1State::~IronGolemAttack1State()
{
}

bool IronGolemAttack1State::CheckIdleState(CSSN007MonsterScript * monsterScript)
{
	float curAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object());
	if (curAnimationTimeRatio >= 1.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IronGolemAttack1State * IronGolemAttack1State::GetInstance()
{
	static IronGolemAttack1State instance;
	return &instance;
}

void IronGolemAttack1State::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Attack01", false);
	monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	monsterScript->GetAttackBoxScript()->SetAttackted(false);
}

void IronGolemAttack1State::Update(CSSN007MonsterScript * monsterScript)
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
		SetActiveAttackCollision(monsterScript, 0.4f, 0.6f);
	}
}