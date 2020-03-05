#pragma once
#include "PlayerState.h"

class PlayerRollBackState : public PlayerState
{
public:
	PlayerRollBackState();
	~PlayerRollBackState();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

	void UpdatePosition(CSSN002PlayerScript * playerScript);

public:
	static PlayerRollBackState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

