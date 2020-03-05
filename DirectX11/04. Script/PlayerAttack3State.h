#pragma once
#include "PlayerState.h"

class PlayerAttack3State : public PlayerState
{
private:
	bool mIsNextAttack;

public:
	PlayerAttack3State();
	~PlayerAttack3State();

private:
	virtual bool CheckIdleState(CSSN002PlayerScript * playerScript);

public:
	static PlayerAttack3State* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

