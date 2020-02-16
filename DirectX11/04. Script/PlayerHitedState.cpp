#include "stdafx.h"
#include "PlayerHitedState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerHitedState::PlayerHitedState()
{
}


PlayerHitedState::~PlayerHitedState()
{
}

PlayerHitedState * PlayerHitedState::GetInstance()
{
	static PlayerHitedState instance;
	return &instance;
}

void PlayerHitedState::Init(CSSN002PlayerScript * playerScript)
{
	playerScript->SetHit(false);

	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Damaged", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerHitedState::Update(CSSN002PlayerScript * playerScript)
{
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			PlayerIdleState::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerIdleState::GetInstance());
			break;
		}
	}
}

void PlayerHitedState::Exit(CSSN002PlayerScript * playerScript)
{
}
