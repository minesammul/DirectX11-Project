#include "stdafx.h"
#include "PlayerRollRightState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollRightState::PlayerRollRightState()
{
}


PlayerRollRightState::~PlayerRollRightState()
{
}

PlayerRollRightState * PlayerRollRightState::GetInstance()
{
	static PlayerRollRightState instance;

	return &instance;
}

void PlayerRollRightState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Roll_Right", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

}

void PlayerRollRightState::Update(CSSN002PlayerScript * playerScript)
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

void PlayerRollRightState::Exit(CSSN002PlayerScript * playerScript)
{
}
