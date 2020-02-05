#pragma once
#include "PlayerState.h"

class PlayerWalkFrontState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerWalkFrontState();
	~PlayerWalkFrontState();

public:
	static PlayerWalkFrontState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};

