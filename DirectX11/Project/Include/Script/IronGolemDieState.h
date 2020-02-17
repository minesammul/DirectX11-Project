#pragma once
#include "MonsterState.h"

class IronGolemDieState : public MonsterState
{
private:
	int findAnimationIndex;

public:
	IronGolemDieState();
	~IronGolemDieState();

public:
	static IronGolemDieState* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
	virtual void Exit(CSSN007MonsterScript * monsterScript) override;
};

