#include "stdafx.h"
#include "PlayerAttackState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerAttackState::PlayerAttackState()
{
}


PlayerAttackState::~PlayerAttackState()
{
}

PlayerAttackState * PlayerAttackState::GetInstance()
{
	static PlayerAttackState instance;

	return &instance;
}

void PlayerAttackState::Init(CSSN002PlayerScript * playerScript)
{
	curAnimationIndex = (int)ATTACK_TYPE::ATTACK1;
	isNextAttack = false;

	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack1", findAnimationIndex[(int)ATTACK_TYPE::ATTACK1]) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex[(int)ATTACK_TYPE::ATTACK1], 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex[(int)ATTACK_TYPE::ATTACK1]);
	}

	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack2", findAnimationIndex[(int)ATTACK_TYPE::ATTACK2]) == false)
		{
			assert(false && L"Not Find Animation");
		}
	}

	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack3", findAnimationIndex[(int)ATTACK_TYPE::ATTACK3]) == false)
		{
			assert(false && L"Not Find Animation");
		}
	}

	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack4", findAnimationIndex[(int)ATTACK_TYPE::ATTACK4]) == false)
		{
			assert(false && L"Not Find Animation");
		}
	}
	//
}

void PlayerAttackState::Update(CSSN002PlayerScript * playerScript)
{
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			curAnimationIndex++;

			if ((curAnimationIndex < (int)ATTACK_TYPE::END) && isNextAttack == true)
			{
				isNextAttack = false;

				for (int i = 0; i < playerScript->Object()->GetChild().size(); i++)
				{
					playerScript->Object()->GetChild()[i]->Animator3D()->SetClipTime(findAnimationIndex[curAnimationIndex], 0.f);
					playerScript->Object()->GetChild()[i]->Animator3D()->SetCurAnimClip(findAnimationIndex[curAnimationIndex]);
				}

			}
			else
			{
				PlayerIdleState::GetInstance()->Init(playerScript);
				playerScript->SetState(PlayerIdleState::GetInstance());
			}

			break;
		}
		else
		{
			float curRatioAnimTime = playerScript->Object()->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
			if (curRatioAnimTime >= 0.5f)
			{
				if (KEYTAB(KEY_TYPE::KEY_LBTN))
				{
					isNextAttack = true;
				}
			}
		}
	}
}

void PlayerAttackState::Exit(CSSN002PlayerScript * playerScript)
{
}
