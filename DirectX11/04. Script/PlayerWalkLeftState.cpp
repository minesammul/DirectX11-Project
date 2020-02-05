#include "stdafx.h"
#include "PlayerWalkLeftState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollLeftState.h"
#include "PlayerAttackState.h"
#include "PlayerHealState.h"
#include "PlayerParryingState.h"

PlayerWalkLeftState::PlayerWalkLeftState()
{
}


PlayerWalkLeftState::~PlayerWalkLeftState()
{
}

PlayerWalkLeftState * PlayerWalkLeftState::GetInstance()
{
	static PlayerWalkLeftState instance;

	return &instance;
}

void PlayerWalkLeftState::Init(CSSN002PlayerScript * playerScript)
{	
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Walk_Left", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerWalkLeftState::Update(CSSN002PlayerScript * playerScript)
{
	if (KEYHOLD(KEY_TYPE::KEY_A))
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
	else if (KEYAWAY(KEY_TYPE::KEY_A))
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		PlayerRollLeftState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollLeftState::GetInstance());
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

void PlayerWalkLeftState::Exit(CSSN002PlayerScript * playerScript)
{
}
