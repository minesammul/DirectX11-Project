#pragma once
#include "PlayerState.h"

class PlayerIdleState : public PlayerState
{
private:
	int mFindAnimationIndex;


public:
	PlayerIdleState();
	~PlayerIdleState();

public:
	// PlayerState��(��) ���� ��ӵ�
	static PlayerIdleState* GetInstance();
	virtual void Init(CSSN002PlayerScript* playerScript) override;
	virtual void Update(CSSN002PlayerScript* playerScript) override;
};

