#pragma once
#include "MonsterState.h"

class IronGolemRotateLeftState : public MonsterState
{
public:
	IronGolemRotateLeftState();
	~IronGolemRotateLeftState();

private:
	virtual bool CheckIdleState(CSSN007MonsterScript * monsterScript);

public:
	static IronGolemRotateLeftState* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

