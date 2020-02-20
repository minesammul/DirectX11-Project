#include "stdafx.h"
#include "PlayerHitedState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"

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
}

void PlayerHitedState::Update(CSSN002PlayerScript * playerScript)
{
	playerScript->RestoreSP();

	PlayerIdleState::GetInstance()->Init(playerScript);
	playerScript->SetState(PlayerIdleState::GetInstance());
}

void PlayerHitedState::Exit(CSSN002PlayerScript * playerScript)
{
}
