#pragma once
#include "MonsterState.h"

class IronGolemWalkFrontState : public MonsterState
{
private:
	const float PLAYER_FIND_DISTANCE;

private:
	int findAnimationIndex;

public:
	IronGolemWalkFrontState();
	~IronGolemWalkFrontState();

public:
	static IronGolemWalkFrontState* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

