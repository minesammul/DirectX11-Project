#include "stdafx.h"
#include "PlayerWalkRightState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollRightState.h"
#include "PlayerAttack1State.h"
#include "PlayerHealSuccessState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"

PlayerWalkRightState::PlayerWalkRightState()
{
}


PlayerWalkRightState::~PlayerWalkRightState()
{
}

PlayerWalkRightState * PlayerWalkRightState::GetInstance()
{
	static PlayerWalkRightState instance;

	return &instance;
}

void PlayerWalkRightState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Walk_Right", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerWalkRightState::Update(CSSN002PlayerScript * playerScript)
{
	playerScript->RestoreSP();

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

	if (KEYHOLD(KEY_TYPE::KEY_D))
	{
		if (playerScript->GetPlayerMovable() == false)
		{
			Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
			playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
			return;
		}


		// Animation Done is Init
		for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
		{
			if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
			{
				continue;
			}

			if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
			{
				playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
				playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
			}
		}
		//

		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MainCamera", findObject);

		Vec3 walkDirection = findObject[0]->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
		walkDirection.y = 0.f;

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerMoveSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_D))
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		if (playerScript->CanUseSP(PlayerRollRightState::GetInstance()->GetUseSPAmount()) == true)
		{
			PlayerRollRightState::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerRollRightState::GetInstance());
		}
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		if (playerScript->CanUseSP(PlayerAttack1State::GetInstance()->GetUseSPAmount()) == true)
		{
			PlayerAttack1State::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerAttack1State::GetInstance());
		}
	}

	if (KEYTAB(KEY_TYPE::KEY_E))
	{
		PlayerHealSuccessState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealSuccessState::GetInstance());
	}
}

void PlayerWalkRightState::Exit(CSSN002PlayerScript * playerScript)
{
}
