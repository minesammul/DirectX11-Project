#include "stdafx.h"
#include "PlayerHitedState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "SSN008AttackBoxScript.h"

PlayerHitedState::PlayerHitedState()
{
}


PlayerHitedState::~PlayerHitedState()
{
}

PlayerHitedState * PlayerHitedState::GetInstance()
{
	static PlayerHitedState instance;
	return &instance;
}

void PlayerHitedState::Init(CSSN002PlayerScript * playerScript)
{
	playerScript->SetHit(false);

	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
}

void PlayerHitedState::Update(CSSN002PlayerScript * playerScript)
{
	playerScript->RestoreSP();

	PlayerIdleState::GetInstance()->Init(playerScript);
	playerScript->SetState(PlayerIdleState::GetInstance());
}

