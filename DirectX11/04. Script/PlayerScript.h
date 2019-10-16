#pragma once
#include "Script.h"
class PlayerActionState;

class CPlayerScript :
	public CScript
{
private:
	PlayerActionState* actionState;
	float moveSpeed;
	Vec3 moveDirection;

public:
	CPlayerScript();
	virtual ~CPlayerScript();

private:
	CLONE(CPlayerScript);

private:
	void CalculationMoveDirection();

public:
	virtual void start();
	virtual void update();

	void SetActionState(PlayerActionState* state) { actionState = state; }
	PlayerActionState* GetActionState() { return actionState; }

	float GetMoveSpeed() { return moveSpeed; }

	Vec3 GetMoveDirection() { return moveDirection; }
	void SetMoveDirection(Vec3 direction) { moveDirection = direction; }
};


