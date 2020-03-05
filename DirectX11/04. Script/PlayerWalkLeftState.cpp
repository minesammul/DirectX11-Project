#include "stdafx.h"
#include "PlayerWalkLeftState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollLeftState.h"
#include "PlayerAttack1State.h"
#include "PlayerHealSuccessState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"

PlayerWalkLeftState::PlayerWalkLeftState()
{
}


PlayerWalkLeftState::~PlayerWalkLeftState()
{
}


bool PlayerWalkLeftState::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	return KEYAWAY(KEY_TYPE::KEY_A);
}


PlayerWalkLeftState * PlayerWalkLeftState::GetInstance()
{
	static PlayerWalkLeftState instance;
	return &instance;
}

void PlayerWalkLeftState::Init(CSSN002PlayerScript * playerScript)
{	
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Walk_Left", true);
}

void PlayerWalkLeftState::Update(CSSN002PlayerScript * playerScript)
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
	else if (CheckRollState(playerScript, PlayerRollLeftState::GetInstance()->GetUseSPAmount()) == true)
	{
		PlayerRollLeftState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollLeftState::GetInstance());
	}
	else if (CheckAttackState(playerScript, PlayerAttack1State::GetInstance()->GetUseSPAmount(), 0.f, 1.f, nullptr) == true)
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

		CGameObject* mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");
		Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT) * (-1.f);
		UpdatePosition(playerScript, moveDirection, playerScript->GetPlayerMoveSpeed(), 0.f, 1.f);
	}
}
