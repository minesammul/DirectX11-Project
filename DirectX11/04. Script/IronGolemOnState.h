#pragma once
#include "MonsterState.h"

class IronGolemOnState : public MonsterState
{
private:
	int findAnimationIndex;

public:
	IronGolemOnState();
	~IronGolemOnState();

public:
	static IronGolemOnState* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;

};

