#include "stdafx.h"
#include "IronGolemOnState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"

IronGolemOnState::IronGolemOnState()
{
}


IronGolemOnState::~IronGolemOnState()
{
}

IronGolemOnState * IronGolemOnState::GetInstance()
{
	static IronGolemOnState instance;
	return &instance;
}

void IronGolemOnState::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"MonsterOn", false);
}

void IronGolemOnState::Update(CSSN007MonsterScript * monsterScript)
{
	float curAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object());
	if (curAnimationTimeRatio >= 1.f)
	{
		IronGolemIdleState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemIdleState::GetInstance());
	}
}
