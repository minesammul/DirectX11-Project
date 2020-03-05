#pragma once
#include "PlayerState.h"

class PlayerDeadState : public PlayerState
{
public:
	PlayerDeadState();
	~PlayerDeadState();

public:
	static PlayerDeadState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

