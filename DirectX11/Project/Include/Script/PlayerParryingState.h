#pragma once
#include "PlayerState.h"

class PlayerParryingState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerParryingState();
	~PlayerParryingState();

public:
	static PlayerParryingState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

