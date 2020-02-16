#pragma once
#include "MonsterState.h"

class IronGolemAttack1State : public MonsterState
{
private:
	int findAnimationIndex;

public:
	IronGolemAttack1State();
	~IronGolemAttack1State();

public:
	static IronGolemAttack1State* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
	virtual void Exit(CSSN007MonsterScript * monsterScript) override;
};

