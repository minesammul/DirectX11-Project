#pragma once
#include "PlayerState.h"

class PlayerAttack1State : public PlayerState
{
private:
	int findAnimationIndex;
	bool isNextAttack;

public:
	PlayerAttack1State();
	~PlayerAttack1State();

public:
	static PlayerAttack1State* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

