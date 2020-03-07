#include "stdafx.h"
#include "IronGolemDieState.h"

#include "SSN007MonsterScript.h"
#include "SSN008AttackBoxScript.h"

IronGolemDieState::IronGolemDieState()
{
}


IronGolemDieState::~IronGolemDieState()
{
}

IronGolemDieState * IronGolemDieState::GetInstance()
{
	static IronGolemDieState instance;
	return &instance;
}

void IronGolemDieState::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Dead", false);
	monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	monsterScript->GetAttackBoxScript()->SetAttackted(false);
}

void IronGolemDieState::Update(CSSN007MonsterScript * monsterScript)
{
}
