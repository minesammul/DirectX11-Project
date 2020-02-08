#pragma once
#include "PlayerState.h"

class PlayerRollRightState : public PlayerState
{
private:
	int findAnimationIndex;
	bool isMove;

public:
	PlayerRollRightState();
	~PlayerRollRightState();

public:
	static PlayerRollRightState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

