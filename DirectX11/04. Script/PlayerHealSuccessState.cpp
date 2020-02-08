#include "stdafx.h"
#include "PlayerHealSuccessState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

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
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Heal_Success", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerHealSuccessState::Update(CSSN002PlayerScript * playerScript)
{
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			PlayerIdleState::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerIdleState::GetInstance());
			break;
		}
	}
}

void PlayerHealSuccessState::Exit(CSSN002PlayerScript * playerScript)
{
}
