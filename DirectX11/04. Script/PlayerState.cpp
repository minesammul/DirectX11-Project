#include "stdafx.h"
#include "PlayerState.h"
#include "SSN002PlayerScript.h"


PlayerState::PlayerState() : 
	mUseSPAmount(0)
{
}


PlayerState::~PlayerState()
{
}

bool PlayerState::CheckDieState(CSSN002PlayerScript* playerScript)
{
	return playerScript->GetDead();
}

bool PlayerState::CheckHitedState(CSSN002PlayerScript * playerScript)
{
	return playerScript->GetHit();
}

bool PlayerState::CheckWalkFrontState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_W);
}

bool PlayerState::CheckWalkBackState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_S);
}

bool PlayerState::CheckWalkLeftState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_A);
}

bool PlayerState::CheckWalkRightState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_D);
}

bool PlayerState::CheckHealState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_E);
}

bool PlayerState::CheckAttack1State(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_LBTN);
}
