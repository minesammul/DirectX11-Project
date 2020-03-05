#include "stdafx.h"
#include "PlayerWalkBackState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollBackState.h"
#include "PlayerAttack1State.h"
#include "PlayerHealSuccessState.h"
#include "PlayerDeadState.h"
#include "PlayerHitedState.h"

PlayerWalkBackState::PlayerWalkBackState()
{
}


PlayerWalkBackState::~PlayerWalkBackState()
{
}


bool PlayerWalkBackState::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	return KEYAWAY(KEY_TYPE::KEY_S);
}


PlayerWalkBackState * PlayerWalkBackState::GetInstance()
{
	static PlayerWalkBackState instance;
	return &instance;
}

void PlayerWalkBackState::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Walk_Back", true);
}

void PlayerWalkBackState::Update(CSSN002PlayerScript * playerScript)
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
	else if (CheckRollState(playerScript, PlayerRollBackState::GetInstance()->GetUseSPAmount()) == true)
	{
		PlayerRollBackState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollBackState::GetInstance());
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
		Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT) *(-1.f);
		UpdatePosition(playerScript, moveDirection, playerScript->GetPlayerMoveSpeed(), 0.f, 1.f);
	}
}
