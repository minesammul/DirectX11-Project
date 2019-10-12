#include "stdafx.h"
#include "PlayerScript.h"
#include "PlayerActionState.h"
#include "PlayerActionStateIdle.h"
#include "PlayerActionStateMove.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
{
	actionState = new PlayerActionStateIdle;
	moveSpeed = 200.f;
}

CPlayerScript::~CPlayerScript()
{
	delete actionState;
}

void CPlayerScript::start()
{
}

void CPlayerScript::update()
{
	actionState->Update(this);
}
