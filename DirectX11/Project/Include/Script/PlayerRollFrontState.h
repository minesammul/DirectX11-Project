#pragma once
#include "PlayerState.h"

class PlayerRollFrontState : public PlayerState
{
public:
	PlayerRollFrontState();
	~PlayerRollFrontState();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

	void UpdatePosition(CSSN002PlayerScript * playerScript);

public:
	static PlayerRollFrontState* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

