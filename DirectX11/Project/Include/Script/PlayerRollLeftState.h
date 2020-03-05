#pragma once
#include "PlayerState.h"

class PlayerRollLeftState : public PlayerState
{
public:
	PlayerRollLeftState();
	~PlayerRollLeftState();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerRollLeftState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

