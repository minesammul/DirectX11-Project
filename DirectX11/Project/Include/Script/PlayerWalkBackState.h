#pragma once
#include "PlayerState.h"

class PlayerWalkBackState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerWalkBackState();
	~PlayerWalkBackState();

public:
	static PlayerWalkBackState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

