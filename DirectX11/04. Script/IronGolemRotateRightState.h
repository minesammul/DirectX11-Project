#pragma once
#include "MonsterState.h"

class IronGolemRotateRightState : public MonsterState
{
private:
	int findAnimationIndex;

public:
	IronGolemRotateRightState();
	~IronGolemRotateRightState();

public:
	static IronGolemRotateRightState* GetInstance();

	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
	virtual void Exit(CSSN007MonsterScript * monsterScript) override;
};

