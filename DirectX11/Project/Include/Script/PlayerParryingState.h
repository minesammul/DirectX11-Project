#pragma once
#include "PlayerState.h"

class PlayerParryingState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerParryingState();
	~PlayerParryingState();

public:
	static PlayerParryingState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

