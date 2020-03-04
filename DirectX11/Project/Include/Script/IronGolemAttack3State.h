#pragma once
#include "MonsterState.h"

class IronGolemAttack3State : public MonsterState
{
private:
	int findAnimationIndex;

public:
	IronGolemAttack3State();
	~IronGolemAttack3State();

public:
	static IronGolemAttack3State* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

