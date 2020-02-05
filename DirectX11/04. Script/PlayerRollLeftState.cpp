#include "stdafx.h"
#include "PlayerRollLeftState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollLeftState::PlayerRollLeftState()
{
}


PlayerRollLeftState::~PlayerRollLeftState()
{
}

PlayerRollLeftState * PlayerRollLeftState::GetInstance()
{
	static PlayerRollLeftState instance;

	return &instance;
}

void PlayerRollLeftState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Roll_Left", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

}

void PlayerRollLeftState::Update(CSSN002PlayerScript * playerScript)
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

void PlayerRollLeftState::Exit(CSSN002PlayerScript * playerScript)
{
}
