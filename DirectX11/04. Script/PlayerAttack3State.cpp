#include "stdafx.h"
#include "PlayerAttack3State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack4State.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack3State::PlayerAttack3State()
{
}


PlayerAttack3State::~PlayerAttack3State()
{
}

bool PlayerAttack3State::CheckIdleState(CSSN002PlayerScript * playerScript)
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

PlayerAttack3State * PlayerAttack3State::GetInstance()
{
	static PlayerAttack3State instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerAttack3State::Init(CSSN002PlayerScript * playerScript)
{
	mIsNextAttack = false;
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Attack06", false);
	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerAttack3State::Update(CSSN002PlayerScript * playerScript)
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
	else if (CheckAttackState(playerScript, PlayerAttack4State::GetInstance()->GetUseSPAmount(), 0.5f, 1.f, &mIsNextAttack) == true)
	{
		PlayerAttack4State::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttack4State::GetInstance());
	}
	else if (CheckIdleState(playerScript) == true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else
	{
		SetActiveAttackCollision(playerScript, 0.4f, 1.0f);
	}
}

