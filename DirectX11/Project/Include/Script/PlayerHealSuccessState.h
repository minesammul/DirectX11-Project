#pragma once
#include "PlayerState.h"


class PlayerHealSuccessState : public PlayerState
{
private:
	int mHealValue;

public:
	PlayerHealSuccessState();
	~PlayerHealSuccessState();

public:
	static PlayerHealSuccessState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

