#pragma once
#include "PlayerState.h"

class PlayerIdleState : public PlayerState
{
public:
	PlayerIdleState();
	~PlayerIdleState();

public:
	// PlayerState을(를) 통해 상속됨
	static PlayerIdleState* GetInstance();
	virtual void Init(CSSN002PlayerScript* playerScript) override;
	virtual void Update(CSSN002PlayerScript* playerScript) override;
};

