#pragma once
#include "PlayerState.h"

class PlayerAttack4State : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerAttack4State();
	~PlayerAttack4State();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerAttack4State* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};