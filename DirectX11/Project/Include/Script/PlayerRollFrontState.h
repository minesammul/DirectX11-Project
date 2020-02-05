#pragma once
#include "PlayerState.h"

class PlayerRollFrontState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerRollFrontState();
	~PlayerRollFrontState();

public:
	static PlayerRollFrontState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

