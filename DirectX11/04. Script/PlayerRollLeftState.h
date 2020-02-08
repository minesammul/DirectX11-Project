#pragma once
#include "PlayerState.h"

class PlayerRollLeftState : public PlayerState
{
private:
	int findAnimationIndex;
	bool isMove;

public:
	PlayerRollLeftState();
	~PlayerRollLeftState();

public:
	static PlayerRollLeftState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

