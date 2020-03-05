#include "stdafx.h"
#include "PlayerDeadState.h"

#include "SSN002PlayerScript.h"
#include "SSN008AttackBoxScript.h"

PlayerDeadState::PlayerDeadState()
{
}


PlayerDeadState::~PlayerDeadState()
{
}

PlayerDeadState * PlayerDeadState::GetInstance()
{
	static PlayerDeadState instance;
	return &instance;
}

void PlayerDeadState::Init(CSSN002PlayerScript * playerScript)
{	
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Dead", false);
	playerScript->GetAttackBoxScript()->SetActiveCollision(false);
	playerScript->GetAttackBoxScript()->SetAttackted(false);
}

void PlayerDeadState::Update(CSSN002PlayerScript * playerScript)
{
}


