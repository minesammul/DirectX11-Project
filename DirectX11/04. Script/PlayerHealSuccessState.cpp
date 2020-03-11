#include "stdafx.h"
#include "PlayerHealSuccessState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "EventQueueMgr.h"

PlayerHealSuccessState::PlayerHealSuccessState()
{
}


PlayerHealSuccessState::~PlayerHealSuccessState()
{
}

PlayerHealSuccessState * PlayerHealSuccessState::GetInstance()
{
	static PlayerHealSuccessState instance;
	return &instance;
}

void PlayerHealSuccessState::Init(CSSN002PlayerScript * playerScript)
{
	mHealValue = 1;
}

void PlayerHealSuccessState::Update(CSSN002PlayerScript * playerScript)
{
	if (CheckDieState(playerScript) == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}
	else if (CheckHitedState(playerScript) == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
	}
	else
	{
		playerScript->RestoreSP();
		if (playerScript->UseHeal(mHealValue) == true)
		{
			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::PLAYER_ITEM_HEAL_UPDATE;
				addEvent.sendObjectName = playerScript->Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}

			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::PLAYER_HP_UPDATE;
				addEvent.sendObjectName = playerScript->Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}

			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::PARTICLE_HEAL_START;
				addEvent.sendObjectName = playerScript->Object()->GetName();
				addEvent.receiveObjectName = L"ParticleHeal1";
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
		}

		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());

	}
}
