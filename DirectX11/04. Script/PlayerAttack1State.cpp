#include "stdafx.h"
#include "PlayerAttack1State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack2State.h"
#include "SSN008AttackBoxScript.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"

PlayerAttack1State::PlayerAttack1State()
{
}


PlayerAttack1State::~PlayerAttack1State()
{
}

PlayerAttack1State * PlayerAttack1State::GetInstance()
{
	static PlayerAttack1State instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerAttack1State::Init(CSSN002PlayerScript * playerScript)
{
	isNextAttack = false;

	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack01", findAnimationIndex) == false)
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

void PlayerAttack1State::Update(CSSN002PlayerScript * playerScript)
{
	if (playerScript->GetDead() == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}

	if (playerScript->GetHit() == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
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
				PlayerAttack2State::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerAttack2State::GetInstance());
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
					if (playerScript->CanUseSP(PlayerAttack2State::GetInstance()->GetUseSPAmount()) == true)
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

void PlayerAttack1State::Exit(CSSN002PlayerScript * playerScript)
{
}
