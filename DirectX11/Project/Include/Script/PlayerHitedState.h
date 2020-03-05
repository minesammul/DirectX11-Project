#pragma once
#include "PlayerState.h"

class PlayerHitedState : public PlayerState
{
public:
	PlayerHitedState();
	~PlayerHitedState();

public:
	static PlayerHitedState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

