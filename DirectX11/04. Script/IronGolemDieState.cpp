#include "stdafx.h"
#include "IronGolemDieState.h"

#include "SSN007MonsterScript.h"
#include "SSN008AttackBoxScript.h"
#include "EventQueueMgr.h"

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

	GameEventComponent addEvent;
	addEvent.eventType = GAME_EVENT_TYPE::SKY_CHANGE_CLEAR;
	addEvent.sendObjectName = monsterScript->Object()->GetName();
	CEventQueueMgr::GetInst()->AddEvent(addEvent);
}

void IronGolemDieState::Update(CSSN007MonsterScript * monsterScript)
{
}
