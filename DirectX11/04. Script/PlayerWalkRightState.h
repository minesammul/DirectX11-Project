#pragma once
#include "PlayerState.h"

class PlayerWalkRightState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerWalkRightState();
	~PlayerWalkRightState();

public:
	static PlayerWalkRightState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

