#include "stdafx.h"
#include "PlayerAttack1State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack2State.h"
#include "SSN008AttackBoxScript.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"

PlayerAttack1State::PlayerAttack1State()
{
}


PlayerAttack1State::~PlayerAttack1State()
{
}

bool PlayerAttack1State::CheckIdleState(CSSN002PlayerScript * playerScript)
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

PlayerAttack1State * PlayerAttack1State::GetInstance()
{
	static PlayerAttack1State instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerAttack1State::Init(CSSN002PlayerScript * playerScript)
{
	mIsNextAttack = false;
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Attack01", false);
	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerAttack1State::Update(CSSN002PlayerScript * playerScript)
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
	else if (CheckAttackState(playerScript, PlayerAttack2State::GetInstance()->GetUseSPAmount(), 0.5f, 1.f, &mIsNextAttack) == true)
	{
		PlayerAttack2State::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttack2State::GetInstance());
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