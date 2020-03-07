#pragma once
#include "MonsterState.h"

class IronGolemRotateRightState : public MonsterState
{
public:
	IronGolemRotateRightState();
	~IronGolemRotateRightState();

private:
	virtual bool CheckIdleState(CSSN007MonsterScript * monsterScript);

public:
	static IronGolemRotateRightState* GetInstance();

	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

