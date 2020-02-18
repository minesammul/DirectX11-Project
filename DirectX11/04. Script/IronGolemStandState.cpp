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
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Stand", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void IronGolemStandState::Update(CSSN007MonsterScript * monsterScript)
{
	{
		Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
		Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

		float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

		if (monsterToPlayerDistance < 500.f)
		{
			IronGolemOnState::GetInstance()->Init(monsterScript);
			monsterScript->SetState(IronGolemOnState::GetInstance());

			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::ON_MONSTER_UI;
			addEvent.sendObjectName = monsterScript->Object()->GetName();
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
	}

}

void IronGolemStandState::Exit(CSSN007MonsterScript * monsterScript)
{
}
