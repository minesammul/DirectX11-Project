#include "stdafx.h"
#include "IronGolemAttack3State.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "SSN008AttackBoxScript.h"
#include "IronGolemDieState.h"
#include "EventQueueMgr.h"

IronGolemAttack3State::IronGolemAttack3State()
{
}


IronGolemAttack3State::~IronGolemAttack3State()
{
}

bool IronGolemAttack3State::CheckIdleState(CSSN007MonsterScript * monsterScript)
{
	float curAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object());

	if (curAnimationTimeRatio >=1.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IronGolemAttack3State * IronGolemAttack3State::GetInstance()
{
	static IronGolemAttack3State instance;
	return &instance;
}

void IronGolemAttack3State::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Attack03", false);
	monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	monsterScript->GetAttackBoxScript()->SetAttackted(false);
}

void IronGolemAttack3State::Update(CSSN007MonsterScript * monsterScript)
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
		SetActiveAttackCollision(monsterScript, 0.5f, 0.6f);
	}
}
