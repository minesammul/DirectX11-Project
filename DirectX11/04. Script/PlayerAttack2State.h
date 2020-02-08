#pragma once
#include "PlayerState.h"

class PlayerAttack2State : public PlayerState
{
private:
	int findAnimationIndex;
	bool isNextAttack;

public:
	PlayerAttack2State();
	~PlayerAttack2State();

public:
	static PlayerAttack2State* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

