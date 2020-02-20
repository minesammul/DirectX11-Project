#include "stdafx.h"
#include "PlayerAttack3State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack4State.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack3State::PlayerAttack3State()
{
}


PlayerAttack3State::~PlayerAttack3State()
{
}

PlayerAttack3State * PlayerAttack3State::GetInstance()
{
	static PlayerAttack3State instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerAttack3State::Init(CSSN002PlayerScript * playerScript)
{
	isNextAttack = false;

	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack06", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}


	((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetActiveCollision(false);
	((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetAttackted(false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerAttack3State::Update(CSSN002PlayerScript * playerScript)
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
				PlayerAttack4State::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerAttack4State::GetInstance());
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
					if (playerScript->CanUseSP(PlayerAttack4State::GetInstance()->GetUseSPAmount()) == true)
					{
						isNextAttack = true;
					}
				}
			}
		}
	}


	if (animationRatio > 0.4f)
	{
		((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetActiveCollision(true);
	}
}

void PlayerAttack3State::Exit(CSSN002PlayerScript * playerScript)
{
}
