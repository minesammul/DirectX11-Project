#include "stdafx.h"
#include "PlayerRollFrontState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

PlayerRollFrontState::PlayerRollFrontState()
{
}


PlayerRollFrontState::~PlayerRollFrontState()
{
}

bool PlayerRollFrontState::CheckIdleState(CSSN002PlayerScript * playerScript)
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


PlayerRollFrontState * PlayerRollFrontState::GetInstance()
{
	static PlayerRollFrontState instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerRollFrontState::Init(CSSN002PlayerScript * playerScript)
{	
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Roll_Front", false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerRollFrontState::Update(CSSN002PlayerScript * playerScript)
{
	if (CheckIdleState(playerScript) == true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else
	{
		CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");
		Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
		UpdatePosition(playerScript, moveDirection, playerScript->GetPlayerRollSpeed(), 0.f, 0.5f);
	}
}
