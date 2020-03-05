#pragma once
#include "PlayerState.h"

class PlayerHitedState : public PlayerState
{
public:
	PlayerHitedState();
	~PlayerHitedState();

public:
	static PlayerHitedState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

