#pragma once
#include "PlayerState.h"

class PlayerWalkFrontState : public PlayerState
{
public:
	PlayerWalkFrontState();
	~PlayerWalkFrontState();

private:
	bool CheckDieState(CSSN002PlayerScript * playerScript);
	bool CheckHitedState(CSSN002PlayerScript * playerScript);
	bool CheckIdleState(CSSN002PlayerScript * playerScript);
	bool CheckRollFrontState(CSSN002PlayerScript * playerScript);
	bool CheckAttack1State(CSSN002PlayerScript * playerScript);
	bool CheckHealState(CSSN002PlayerScript * playerScript);

public:
	static PlayerWalkFrontState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

