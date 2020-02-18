#include "stdafx.h"
#include "PlayerAttack1State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack2State.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack1State::PlayerAttack1State()
{
}


PlayerAttack1State::~PlayerAttack1State()
{
}

PlayerAttack1State * PlayerAttack1State::GetInstance()
{
	static PlayerAttack1State instance;

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

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack1", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}

	((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetActiveCollision(false);
	((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetAttackted(false);

	playerScript->UseSP(3);
}

void PlayerAttack1State::Update(CSSN002PlayerScript * playerScript)
{
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
				((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetActiveCollision(false);
				PlayerAttack2State::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerAttack2State::GetInstance());
			}
			else
			{
				((CSSN008AttackBoxScript*)playerScript->GetAttackBoxScript())->SetActiveCollision(false);
				PlayerIdleState::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerIdleState::GetInstance());
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
					isNextAttack = true;
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
