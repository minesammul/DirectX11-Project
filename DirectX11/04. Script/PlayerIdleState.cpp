#include "stdafx.h"
#include "PlayerIdleState.h"

#include "SSN002PlayerScript.h"
#include "PlayerWalkFrontState.h"
#include "PlayerWalkBackState.h"
#include "PlayerWalkLeftState.h"
#include "PlayerWalkRightState.h"
#include "PlayerHealSuccessState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "PlayerAttack1State.h"
#include "SSN008AttackBoxScript.h"

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
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Idle", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
}

void PlayerIdleState::Update(CSSN002PlayerScript* playerScript)
{
	playerScript->RestoreSP();

	// Animation Done is Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
			playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
		}
	}
	//

	if (playerScript->GetDead() == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
		return;
	}

	if (playerScript->GetHit() == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
		return;
	}

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
		PlayerHealSuccessState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealSuccessState::GetInstance());
	}
	//

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		if (playerScript->CanUseSP(PlayerAttack1State::GetInstance()->GetUseSPAmount()) == true)
		{
			PlayerAttack1State::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerAttack1State::GetInstance());
		}
	}
}

void PlayerIdleState::Exit(CSSN002PlayerScript* playerScript)
{

}
