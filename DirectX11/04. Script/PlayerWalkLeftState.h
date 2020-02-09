#pragma once
#include "PlayerState.h"

class PlayerWalkLeftState : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerWalkLeftState();
	~PlayerWalkLeftState();

public:
	static PlayerWalkLeftState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};
