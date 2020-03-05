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

bool PlayerRollRightState::CheckIdleState(CSSN002PlayerScript * playerScript)
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


PlayerRollRightState * PlayerRollRightState::GetInstance()
{
	static PlayerRollRightState instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerRollRightState::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Roll_Right", false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerRollRightState::Update(CSSN002PlayerScript * playerScript)
{
	if (CheckIdleState(playerScript)==true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else
	{
		CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");
		Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
		UpdatePosition(playerScript, moveDirection, playerScript->GetPlayerRollSpeed(), 0.f, 0.5f);
	}
}