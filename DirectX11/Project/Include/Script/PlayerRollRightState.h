#pragma once
#include "PlayerState.h"

class PlayerRollRightState : public PlayerState
{
public:
	PlayerRollRightState();
	~PlayerRollRightState();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerRollRightState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

