#pragma once
#include "PlayerState.h"

enum class ATTACK_TYPE
{
	ATTACK1=0,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	END
};

class PlayerAttackState : public PlayerState
{
private:
	int findAnimationIndex[(int)ATTACK_TYPE::END];
	int curAnimationIndex;
	bool isNextAttack;

public:
	PlayerAttackState();
	~PlayerAttackState();

public:
	static PlayerAttackState* GetInstance();

	// PlayerState을(를) 통해 상속됨
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

