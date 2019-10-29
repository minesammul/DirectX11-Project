#pragma once
#include "Script.h"
class PlayerActionState;

struct PlayerData
{
	int maxHp;
	int nowHp;
};

class CPlayerScript :
	public CScript
{
private:
	PlayerActionState* actionState;
	float moveSpeed;
	Vec3 moveDirection;
	Vec3 mouseDirection;

	CResPtr<CMaterial> cloneMtrl;

	PlayerData playerData;
	bool isHited;

public:
	CPlayerScript();
	virtual ~CPlayerScript();

private:
	CLONE(CPlayerScript);

private:
	void CalculationMoveDirection();
	void CalculationMouseDirection();

public:
	virtual void start();
	virtual void update();

	void SetActionState(PlayerActionState* state) { actionState = state; }
	PlayerActionState* GetActionState() { return actionState; }

	float GetMoveSpeed() { return moveSpeed; }

	Vec3 GetMoveDirection() { return moveDirection; }
	void SetMoveDirection(Vec3 direction) { moveDirection = direction; }

	Vec3 GetMouseDirection() { return mouseDirection; }

	void SendPlayerDataToEventQueue(void);
	void PlayerHited(void);
};


