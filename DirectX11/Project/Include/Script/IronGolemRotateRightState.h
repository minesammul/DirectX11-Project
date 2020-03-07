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

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

