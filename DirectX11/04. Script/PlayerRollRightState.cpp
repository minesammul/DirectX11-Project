#include "stdafx.h"
#include "PlayerRollRightState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollRightState::PlayerRollRightState()
{
}


PlayerRollRightState::~PlayerRollRightState()
{
}

PlayerRollRightState * PlayerRollRightState::GetInstance()
{
	static PlayerRollRightState instance;

	return &instance;
}

void PlayerRollRightState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Roll_Right", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

	playerScript->UseSP(3);

}

void PlayerRollRightState::Update(CSSN002PlayerScript * playerScript)
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

void PlayerRollRightState::Exit(CSSN002PlayerScript * playerScript)
{
}
