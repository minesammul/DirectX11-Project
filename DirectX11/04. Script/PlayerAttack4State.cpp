#include "stdafx.h"
#include "PlayerAttack4State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerAttack4State::PlayerAttack4State()
{
}


PlayerAttack4State::~PlayerAttack4State()
{
}

PlayerAttack4State * PlayerAttack4State::GetInstance()
{
	static PlayerAttack4State instance;
	return &instance;
}

void PlayerAttack4State::Init(CSSN002PlayerScript * playerScript)
{
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack4", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
}

void PlayerAttack4State::Update(CSSN002PlayerScript * playerScript)
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

void PlayerAttack4State::Exit(CSSN002PlayerScript * playerScript)
{
}
