#pragma once
#include "Script.h"
class PlayerActionState;

class CPlayerScript :
	public CScript
{
private:
	PlayerActionState* actionState;
	float moveSpeed;

public:
	CPlayerScript();
	virtual ~CPlayerScript();

private:
	CLONE(CPlayerScript);

public:
	virtual void start();
	virtual void update();

	void SetActionState(PlayerActionState* state) { actionState = state; }
	PlayerActionState* GetActionState() { return actionState; }

	float GetMoveSpeed() { return moveSpeed; }
};


