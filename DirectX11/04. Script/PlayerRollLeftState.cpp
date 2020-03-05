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
		CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");
		Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT) * (-1.f);
		UpdatePosition(playerScript, moveDirection, playerScript->GetPlayerRollSpeed(), 0.f, 0.5f);
	}
}

