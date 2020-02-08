#pragma once
#include "PlayerState.h"


class PlayerHealSuccessState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerHealSuccessState();
	~PlayerHealSuccessState();

public:
	static PlayerHealSuccessState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

