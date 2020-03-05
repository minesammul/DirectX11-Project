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
		CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");
		Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT) * (-1.f);
		UpdatePosition(playerScript, moveDirection, playerScript->GetPlayerRollSpeed(), 0.f, 0.5f);
	}
}

