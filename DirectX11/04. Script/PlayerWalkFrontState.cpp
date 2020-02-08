#include "stdafx.h"
#include "PlayerWalkFrontState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollFrontState.h"
#include "PlayerAttackState.h"
#include "PlayerHealState.h"
#include "PlayerParryingState.h"
#include <Camera.h>

PlayerWalkFrontState::PlayerWalkFrontState()
{
}


PlayerWalkFrontState::~PlayerWalkFrontState()
{
}

PlayerWalkFrontState * PlayerWalkFrontState::GetInstance()
{
	static PlayerWalkFrontState instance;
	return &instance;
}

void PlayerWalkFrontState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Walk_Front", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerWalkFrontState::Update(CSSN002PlayerScript * playerScript)
{
	if (KEYHOLD(KEY_TYPE::KEY_W))
	{
		// Animation Done is Init
		for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
		{
			if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
			{
				playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
				playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
			}
		}
		//

		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MainCamera", findObject);

		Vec3 walkDirection = findObject[0]->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerMoveSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}
	else if(KEYAWAY(KEY_TYPE::KEY_W))
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		PlayerRollFrontState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollFrontState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		PlayerAttackState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttackState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_E))
	{
		PlayerHealState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_RBTN))
	{
		PlayerParryingState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerParryingState::GetInstance());
	}
}

void PlayerWalkFrontState::Exit(CSSN002PlayerScript * playerScript)
{
}
