#include "stdafx.h"
#include "IronGolemDieState.h"

#include "SSN007MonsterScript.h"
#include "SSN008AttackBoxScript.h"
#include "SSN013MusicScript.h"
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

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::SKY_CHANGE_CLEAR;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::PARTICLE_RAIN_STOP;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}
	
	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::CLEAR_LIGHT;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::OFF_EFFECT_SOUND_WIND;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::ON_EFFECT_SOUND_BOSSOUT;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::PARTICLE_DOOR_STOP;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::PARTICLE_MONSTER_DEAD_START;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		addEvent.receiveObjectName = L"ParticleDead1";
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::START_MONSER_DEAD_LIGHT_UI;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

}

void IronGolemDieState::Update(CSSN007MonsterScript * monsterScript)
{
	float nowAnimationRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object());

	if (nowAnimationRatio >= 1.000f)
	{
		monsterScript->Object()->Active(false);
	}
}
