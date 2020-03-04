#include "stdafx.h"
#include "PlayerAttack2State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack3State.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack2State::PlayerAttack2State()
{
}


PlayerAttack2State::~PlayerAttack2State()
{
}

PlayerAttack2State * PlayerAttack2State::GetInstance()
{
	static PlayerAttack2State instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerAttack2State::Init(CSSN002PlayerScript * playerScript)
{
	isNextAttack = false;

	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack03", findAnimationIndex) == false)
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

void PlayerAttack2State::Update(CSSN002PlayerScript * playerScript)
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
			if (isNextAttack == true)
			{
				PlayerAttack3State::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerAttack3State::GetInstance());
				return;
			}
			else
			{
				PlayerIdleState::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerIdleState::GetInstance());
				return;
			}

			break;
		}
		else
		{
			float curRatioAnimTime = playerScript->Object()->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
			animationRatio = curRatioAnimTime;
			if (curRatioAnimTime >= 0.5f)
			{
				if (KEYTAB(KEY_TYPE::KEY_LBTN))
				{
					if (playerScript->CanUseSP(PlayerAttack3State::GetInstance()->GetUseSPAmount()) == true)
					{
						isNextAttack = true;
					}
				}
			}
		}
	}

	if (animationRatio > 0.4f)
	{
		playerScript->GetAttackBoxScript()->SetActiveCollision(true);
	}
}

