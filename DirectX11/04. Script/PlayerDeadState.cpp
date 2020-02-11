#include "stdafx.h"
#include "PlayerDeadState.h"

#include "SSN002PlayerScript.h"

PlayerDeadState::PlayerDeadState()
{
}


PlayerDeadState::~PlayerDeadState()
{
}

PlayerDeadState * PlayerDeadState::GetInstance()
{
	static PlayerDeadState instance;
	return &instance;
}

void PlayerDeadState::Init(CSSN002PlayerScript * playerScript)
{	
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Dead", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerDeadState::Update(CSSN002PlayerScript * playerScript)
{
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			break;
		}
	}
}

void PlayerDeadState::Exit(CSSN002PlayerScript * playerScript)
{
}
