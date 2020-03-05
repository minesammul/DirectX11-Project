#pragma once
#include "PlayerState.h"

class PlayerAttack4State : public PlayerState
{
public:
	PlayerAttack4State();
	~PlayerAttack4State();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerAttack4State* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};