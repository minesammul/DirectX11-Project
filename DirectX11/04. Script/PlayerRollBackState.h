#pragma once
#include "PlayerState.h"

class PlayerRollBackState : public PlayerState
{
private:
	int findAnimationIndex;
	bool isMove;

public:
	PlayerRollBackState();
	~PlayerRollBackState();

public:
	static PlayerRollBackState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

