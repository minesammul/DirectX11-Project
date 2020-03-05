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

bool PlayerRollBackState::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	float curRatioAnimTime = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());

	if (curRatioAnimTime < 1.f)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void PlayerRollBackState::UpdatePosition(CSSN002PlayerScript * playerScript)
{
	if (playerScript->GetPlayerMovable() == false)
	{
		Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
		playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
	}
	else
	{
		float curRatioAnimTime = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());

		if (curRatioAnimTime <= 0.5f)
		{
			CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");

			Vec3 walkDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
			walkDirection *= -1.f;
			walkDirection.y = 0.f;

			Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
			playerPosition += walkDirection * playerScript->GetPlayerRollSpeed();
			playerScript->Object()->Transform()->SetLocalPos(playerPosition);
		}
	}
}

PlayerRollBackState * PlayerRollBackState::GetInstance()
{
	static PlayerRollBackState instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerRollBackState::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Roll_Back", false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerRollBackState::Update(CSSN002PlayerScript * playerScript)
{
	if (CheckIdleState(playerScript) == true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else
	{
		UpdatePosition(playerScript);
	}
}

