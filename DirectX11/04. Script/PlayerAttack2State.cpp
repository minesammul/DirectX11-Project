#include "stdafx.h"
#include "PlayerAttack2State.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerAttack3State.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "SSN008AttackBoxScript.h"

PlayerAttack2State::PlayerAttack2State()
{
}


PlayerAttack2State::~PlayerAttack2State()
{
}

bool PlayerAttack2State::CheckIdleState(CSSN002PlayerScript * playerScript)
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

PlayerAttack2State * PlayerAttack2State::GetInstance()
{
	static PlayerAttack2State instance;
	instance.SetUseSPAmount(3);
	return &instance;
}

void PlayerAttack2State::Init(CSSN002PlayerScript * playerScript)
{
	mIsNextAttack = false;
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Attack03", false);
	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
	playerScript->UseSP(GetUseSPAmount());
}

void PlayerAttack2State::Update(CSSN002PlayerScript * playerScript)
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
	else if (CheckAttackState(playerScript, PlayerAttack3State::GetInstance()->GetUseSPAmount(), 0.5f, 1.f, &mIsNextAttack) == true)
	{
		PlayerAttack3State::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttack3State::GetInstance());
	}
	else if (CheckIdleState(playerScript) == true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else
	{
		float animationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());
		if (animationTimeRatio > 0.4f)
		{
			playerScript->GetAttackBoxScript()->SetActiveCollision(true);
		}
	}
}

