#include "stdafx.h"
#include "PlayerWalkFrontState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollFrontState.h"
#include "PlayerAttack1State.h"
#include "PlayerHealSuccessState.h"
#include "PlayerDeadState.h"
#include "PlayerHitedState.h"
#include <Camera.h>

PlayerWalkFrontState::PlayerWalkFrontState()
{
}


PlayerWalkFrontState::~PlayerWalkFrontState()
{
}


bool PlayerWalkFrontState::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	return KEYAWAY(KEY_TYPE::KEY_W);
}

void PlayerWalkFrontState::UpdatePosition(CSSN002PlayerScript * playerScript)
{
	if (playerScript->GetPlayerMovable() == false)
	{
		Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
		playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
	}
	else
	{
		CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");

		Vec3 walkDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
		walkDirection.y = 0.f;

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerMoveSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}
}

PlayerWalkFrontState * PlayerWalkFrontState::GetInstance()
{
	static PlayerWalkFrontState instance;
	return &instance;
}

void PlayerWalkFrontState::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Walk_Front", true);
}

void PlayerWalkFrontState::Update(CSSN002PlayerScript * playerScript)
{
	if (CheckDieState(playerScript) == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}
	else if (CheckHitedState(playerScript) == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
	}
	else if (CheckIdleState(playerScript) == true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else if (CheckRollState(playerScript, PlayerRollFrontState::GetInstance()->GetUseSPAmount()) == true)
	{
		PlayerRollFrontState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollFrontState::GetInstance());
	}
	else if (CheckAttack1State(playerScript, PlayerAttack1State::GetInstance()->GetUseSPAmount()) == true)
	{
		PlayerAttack1State::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttack1State::GetInstance());
	}
	else if (CheckHealState(playerScript) == true)
	{
		PlayerHealSuccessState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealSuccessState::GetInstance());
	}
	else
	{
		playerScript->RestoreSP();
		UpdatePosition(playerScript);
	}
}
