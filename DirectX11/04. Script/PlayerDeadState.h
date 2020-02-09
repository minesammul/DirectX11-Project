#pragma once
#include "PlayerState.h"

class PlayerDeadState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerDeadState();
	~PlayerDeadState();

public:
	static PlayerDeadState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};
