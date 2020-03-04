#include "stdafx.h"
#include "PlayerIdleState.h"

#include "SSN002PlayerScript.h"
#include "PlayerWalkFrontState.h"
#include "PlayerWalkBackState.h"
#include "PlayerWalkLeftState.h"
#include "PlayerWalkRightState.h"
#include "PlayerHealSuccessState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "PlayerAttack1State.h"
#include "SSN008AttackBoxScript.h"
#include "FunctionMgr.h"

PlayerIdleState::PlayerIdleState()
{
}


PlayerIdleState::~PlayerIdleState()
{
}

bool PlayerIdleState::CheckDieState(CSSN002PlayerScript* playerScript)
{
	return playerScript->GetDead();
}

bool PlayerIdleState::CheckHitedState(CSSN002PlayerScript * playerScript)
{
	return playerScript->GetHit();
}

bool PlayerIdleState::CheckWalkFrontState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_W);
}

bool PlayerIdleState::CheckWalkBackState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_S);
}

bool PlayerIdleState::CheckWalkLeftState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_A);
}

bool PlayerIdleState::CheckWalkRightState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_D);
}

bool PlayerIdleState::CheckHealState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_E);
}

bool PlayerIdleState::CheckAttack1State(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_LBTN);
}

PlayerIdleState * PlayerIdleState::GetInstance()
{
	static PlayerIdleState instance;
	return &instance;
}

void PlayerIdleState::Init(CSSN002PlayerScript* playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Idle", true);

	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
}

void PlayerIdleState::Update(CSSN002PlayerScript* playerScript)
{
	if (CheckDieState(playerScript) == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}
	else if(CheckHitedState(playerScript)==true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
	}
	else if (CheckWalkFrontState(playerScript) == true)
	{
		PlayerWalkFrontState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkFrontState::GetInstance());
	}
	else if (CheckWalkBackState(playerScript) == true)
	{
		PlayerWalkBackState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkBackState::GetInstance());
	}
	else if (CheckWalkLeftState(playerScript) == true)
	{
		PlayerWalkLeftState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkLeftState::GetInstance());
	}
	else if (CheckWalkRightState(playerScript) == true)
	{
		PlayerWalkRightState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerWalkRightState::GetInstance());
	}
	else if (CheckHealState(playerScript) == true)
	{
		PlayerHealSuccessState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealSuccessState::GetInstance());
	}
	else if (CheckAttack1State(playerScript) == true)
	{
		PlayerAttack1State::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttack1State::GetInstance());
	}
	else
	{
		playerScript->RestoreSP();
	}
}
