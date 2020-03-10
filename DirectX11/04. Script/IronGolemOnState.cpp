#include "stdafx.h"
#include "IronGolemOnState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "EventQueueMgr.h"

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

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::PARTICLE_DOOR_START;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}
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
