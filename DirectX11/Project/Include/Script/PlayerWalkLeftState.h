#pragma once
#include "PlayerState.h"

class PlayerWalkLeftState : public PlayerState
{
public:
	PlayerWalkLeftState();
	~PlayerWalkLeftState();

private:
	bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerWalkLeftState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

