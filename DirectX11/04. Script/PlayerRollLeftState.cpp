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

bool PlayerRollLeftState::CheckIdleState(CSSN002PlayerScript * playerScript)
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

void PlayerRollLeftState::UpdatePosition(CSSN002PlayerScript * playerScript)
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

			Vec3 walkDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
			walkDirection *= -1.f;
			walkDirection.y = 0.f;

			Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
			playerPosition += walkDirection * playerScript->GetPlayerRollSpeed();
			playerScript->Object()->Transform()->SetLocalPos(playerPosition);
		}
	}
}

PlayerRollLeftState * PlayerRollLeftState::GetInstance()
{
	static PlayerRollLeftState instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerRollLeftState::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Roll_Left", false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerRollLeftState::Update(CSSN002PlayerScript * playerScript)
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

