#pragma once
#include "PlayerState.h"

class PlayerWalkFrontState : public PlayerState
{
public:
	PlayerWalkFrontState();
	~PlayerWalkFrontState();

private:
	bool CheckIdleState(CSSN002PlayerScript * playerScript);

	void UpdatePosition(CSSN002PlayerScript * playerScript);

public:
	static PlayerWalkFrontState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

