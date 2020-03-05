#pragma once
#include "PlayerState.h"

class PlayerWalkLeftState : public PlayerState
{
public:
	PlayerWalkLeftState();
	~PlayerWalkLeftState();

private:
	bool CheckDieState(CSSN002PlayerScript * playerScript);
	bool CheckHitedState(CSSN002PlayerScript * playerScript);
	bool CheckIdleState(CSSN002PlayerScript * playerScript);
	bool CheckRollLeftState(CSSN002PlayerScript * playerScript);
	bool CheckAttack1State(CSSN002PlayerScript * playerScript);
	bool CheckHealState(CSSN002PlayerScript * playerScript);

	void UpdatePosition(CSSN002PlayerScript * playerScript);

public:
	static PlayerWalkLeftState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

