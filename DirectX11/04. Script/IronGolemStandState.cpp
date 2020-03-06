#include "stdafx.h"
#include "IronGolemStandState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemOnState.h"
#include "EventQueueMgr.h"

IronGolemStandState::IronGolemStandState() : 
	PLAYER_FIND_DISTANCE(500.f)
{
}


IronGolemStandState::~IronGolemStandState()
{
}

IronGolemStandState * IronGolemStandState::GetInstance()
{
	static IronGolemStandState instance;
	return &instance;
}

void IronGolemStandState::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Stand", false);
}

void IronGolemStandState::Update(CSSN007MonsterScript * monsterScript)
{
	Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
	Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

	float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

	if (monsterToPlayerDistance < PLAYER_FIND_DISTANCE)
	{
		IronGolemOnState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemOnState::GetInstance());

		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::ON_MONSTER_UI;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

}

