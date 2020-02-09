#include "stdafx.h"
#include "PlayerRollBackState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollBackState::PlayerRollBackState()
{
}


PlayerRollBackState::~PlayerRollBackState()
{
}

PlayerRollBackState * PlayerRollBackState::GetInstance()
{
	static PlayerRollBackState instance;

	return &instance;
}

void PlayerRollBackState::Init(CSSN002PlayerScript * playerScript)
{
	//Animation Init
	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Roll_Back", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		playerScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		playerScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void PlayerRollBackState::Update(CSSN002PlayerScript * playerScript)
{
	if (isMove == true)
	{
		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MainCamera", findObject);

		Vec3 walkDirection = findObject[0]->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
		walkDirection *= -1.f;
		walkDirection.y = 0.f;

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerRollSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}


	for (int index = 0; index < playerScript->Object()->GetChild().size(); index++)
	{
		if (playerScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			PlayerIdleState::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerIdleState::GetInstance());
			break;
		}
		else
		{
			float curRatioAnimTime = playerScript->Object()->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
			if (0.2f <= curRatioAnimTime && curRatioAnimTime <= 0.5f)
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

void PlayerRollBackState::Exit(CSSN002PlayerScript * playerScript)
{
}
