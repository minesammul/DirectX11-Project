#pragma once
#include "PlayerState.h"

class PlayerAttack4State : public PlayerState
{
private:
	int findAnimationIndex;

public:
	PlayerAttack4State();
	~PlayerAttack4State();

public:
	static PlayerAttack4State* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;
};