#include "stdafx.h"
#include "PlayerWalkRightState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollRightState.h"
#include "PlayerAttackState.h"
#include "PlayerHealState.h"
#include "PlayerParryingState.h"

PlayerWalkRightState::PlayerWalkRightState()
{
}


PlayerWalkRightState::~PlayerWalkRightState()
{
}

PlayerWalkRightState * PlayerWalkRightState::GetInstance()
{
	static PlayerWalkRightState instance;

	return &instance;
}

void PlayerWalkRightState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Walk_Right", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerWalkRightState::Update(CSSN002PlayerScript * playerScript)
{
	if (KEYHOLD(KEY_TYPE::KEY_D))
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
	}
	else if (KEYAWAY(KEY_TYPE::KEY_D))
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		PlayerRollRightState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollRightState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		PlayerAttackState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttackState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_E))
	{
		PlayerHealState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		PlayerParryingState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerParryingState::GetInstance());
	}
}

void PlayerWalkRightState::Exit(CSSN002PlayerScript * playerScript)
{
}
