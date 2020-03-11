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

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

