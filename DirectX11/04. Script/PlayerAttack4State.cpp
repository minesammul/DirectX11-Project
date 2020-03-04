#include "stdafx.h"
#include "PlayerAttack4State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack4State::PlayerAttack4State()
{
}


PlayerAttack4State::~PlayerAttack4State()
{
}

PlayerAttack4State * PlayerAttack4State::GetInstance()
{
	static PlayerAttack4State instance;
	instance.SetUseSPAmount(1);
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

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack10", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}

	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerAttack4State::Update(CSSN002PlayerScript * playerScript)
{
	if (playerScript->GetDead() == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
		return;
	}

	if (playerScript->GetHit() == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
		return;
	}


	float animationRatio = 0.f;
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
			return;
		}
		else
		{
			animationRatio = playerScript->Object()->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
		}
	}

	if (animationRatio > 0.4f)
	{
		playerScript->GetAttackBoxScript()->SetActiveCollision(true);
	}
}

