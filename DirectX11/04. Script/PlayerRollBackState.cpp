#include "stdafx.h"
#include "PlayerRollBackState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollBackState::PlayerRollBackState()
{
}


PlayerRollBackState::~PlayerRollBackState()
{
}

PlayerRollBackState * PlayerRollBackState::GetInstance()
{
	static PlayerRollBackState instance;

	return &instance;
}

void PlayerRollBackState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Roll_Back", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerRollBackState::Update(CSSN002PlayerScript * playerScript)
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

void PlayerRollBackState::Exit(CSSN002PlayerScript * playerScript)
{
}
