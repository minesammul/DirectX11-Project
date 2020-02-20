#include "stdafx.h"
#include "PlayerRollLeftState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollLeftState::PlayerRollLeftState()
{
}


PlayerRollLeftState::~PlayerRollLeftState()
{
}

PlayerRollLeftState * PlayerRollLeftState::GetInstance()
{
	static PlayerRollLeftState instance;

	return &instance;
}

void PlayerRollLeftState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Roll_Left", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

	playerScript->UseSP(3);

}

void PlayerRollLeftState::Update(CSSN002PlayerScript * playerScript)
{
	if (isMove == true)
	{
		if (playerScript->GetPlayerMovable() == false)
		{
			Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
			playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
			return;
		}

		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MainCamera", findObject);

		Vec3 walkDirection = findObject[0]->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
		walkDirection *= -1.f;
		walkDirection.y = 0.f;

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerRollSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}


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
		else
		{
			float curRatioAnimTime = playerScript->Object()->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
			if (curRatioAnimTime <= 0.5f)
			{
				isMove = true;
			}
			else
			{
				isMove = false;
			}
		}
	}
}

void PlayerRollLeftState::Exit(CSSN002PlayerScript * playerScript)
{
}
