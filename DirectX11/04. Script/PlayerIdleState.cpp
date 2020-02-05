#include "stdafx.h"
#include "PlayerIdleState.h"

#include "SSN002PlayerScript.h"
#include "PlayerWalkFrontState.h"
#include "PlayerWalkBackState.h"
#include "PlayerWalkLeftState.h"
#include "PlayerWalkRightState.h"
#include "PlayerHealState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "PlayerAttackState.h"
#include "PlayerParryingState.h"

PlayerIdleState::PlayerIdleState()
{
	findAnimationIndex = -1;
}


PlayerIdleState::~PlayerIdleState()
{
}

PlayerIdleState * PlayerIdleState::GetInstance()
{
	static PlayerIdleState instance;
	return &instance;
}

void PlayerIdleState::Init(CSSN002PlayerScript* playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Idle", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

}

void PlayerIdleState::Update(CSSN002PlayerScript* playerScript)
{
	// Animation Done is Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
			playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
		}
	}
	//

	// Idle State -> Walk State
	if (KEYTAB(KEY_TYPE::KEY_W))
	{
		PlayerWalkFrontState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkFrontState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_S))
	{
		PlayerWalkBackState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkBackState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_A))
	{
		PlayerWalkLeftState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkLeftState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_D))
	{
		PlayerWalkRightState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkRightState::GetInstance());
	}
	//

	//Idle State -> Heal State
	if (KEYTAB(KEY_TYPE::KEY_E))
	{
		PlayerHealState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealState::GetInstance());
	}
	//

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		PlayerAttackState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttackState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		PlayerParryingState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerParryingState::GetInstance());
	}

}

void PlayerIdleState::Exit(CSSN002PlayerScript* playerScript)
{

}
