#include "stdafx.h"
#include "SSN002PlayerScript.h"

#include "PlayerIdleState.h"

CSSN002PlayerScript::CSSN002PlayerScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT),
	PLAYER_MOVE_SPEED(10.f)
{

}


CSSN002PlayerScript::~CSSN002PlayerScript()
{
}

void CSSN002PlayerScript::start()
{
	playerState = PlayerIdleState::GetInstance();
	playerState->Init(this);
}

void CSSN002PlayerScript::update()
{
	playerState->Update(this);
}

void CSSN002PlayerScript::SetState(PlayerState * state)
{
	playerState = state;
}
