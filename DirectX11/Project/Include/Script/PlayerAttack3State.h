#pragma once
#include "PlayerState.h"

class PlayerAttack3State : public PlayerState
{
private:
	int findAnimationIndex;
	bool isNextAttack;

public:
	PlayerAttack3State();
	~PlayerAttack3State();

public:
	static PlayerAttack3State* GetInstance();

	// PlayerState��(��) ���� ��ӵ�
	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
};

