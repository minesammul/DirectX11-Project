#include "stdafx.h"
#include "PlayerAttack4State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack4State::PlayerAttack4State()
{
}


PlayerAttack4State::~PlayerAttack4State()
{
}

bool PlayerAttack4State::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	float animationTimeRation = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());

	if (animationTimeRation < 1.f)
	{
		return false;
	}
	else
	{
		return true;
	}
}

PlayerAttack4State * PlayerAttack4State::GetInstance()
{
	static PlayerAttack4State instance;
	instance.SetUseSPAmount(1);
	return &instance;
}

void PlayerAttack4State::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Attack10", false);
	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerAttack4State::Update(CSSN002PlayerScript * playerScript)
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
	else
	{
		SetActiveAttackCollision(playerScript, 0.4f, 0.6f);
	}
}

