#include "stdafx.h"
#include "PlayerParryingState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerParryingState::PlayerParryingState()
{
}


PlayerParryingState::~PlayerParryingState()
{
}

PlayerParryingState * PlayerParryingState::GetInstance()
{
	static PlayerParryingState instance;

	return &instance;
}

void PlayerParryingState::Init(CSSN002PlayerScript * playerScript)
{	
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Parrying", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerParryingState::Update(CSSN002PlayerScript * playerScript)
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
