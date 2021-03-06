#pragma once
#include "PlayerState.h"

class PlayerWalkRightState : public PlayerState
{
public:
	PlayerWalkRightState();
	~PlayerWalkRightState();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerWalkRightState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

