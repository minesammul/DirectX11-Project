#include "stdafx.h"
#include "PlayerHealSuccessState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"

PlayerHealSuccessState::PlayerHealSuccessState()
{
}


PlayerHealSuccessState::~PlayerHealSuccessState()
{
}

PlayerHealSuccessState * PlayerHealSuccessState::GetInstance()
{
	static PlayerHealSuccessState instance;
	return &instance;
}

void PlayerHealSuccessState::Init(CSSN002PlayerScript * playerScript)
{

}

void PlayerHealSuccessState::Update(CSSN002PlayerScript * playerScript)
{
	playerScript->RestoreSP();

	if (playerScript->GetDead() == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}

	if (playerScript->GetHit() == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
	}
}

void PlayerHealSuccessState::Exit(CSSN002PlayerScript * playerScript)
{
}
