#pragma once
#include "PlayerState.h"

class PlayerIdleState : public PlayerState
{
public:
	PlayerIdleState();
	~PlayerIdleState();

private:
	bool CheckDieState(CSSN002PlayerScript* playerScript);
	bool CheckHitedState(CSSN002PlayerScript* playerScript);
	bool CheckWalkFrontState(CSSN002PlayerScript* playerScript);
	bool CheckWalkBackState(CSSN002PlayerScript* playerScript);
	bool CheckWalkLeftState(CSSN002PlayerScript* playerScript);
	bool CheckWalkRightState(CSSN002PlayerScript* playerScript);
	bool CheckHealState(CSSN002PlayerScript* playerScript);
	bool CheckAttack1State(CSSN002PlayerScript* playerScript);

public:
	// PlayerState을(를) 통해 상속됨
	static PlayerIdleState* GetInstance();
	virtual void Init(CSSN002PlayerScript* playerScript) override;
	virtual void Update(CSSN002PlayerScript* playerScript) override;
};

