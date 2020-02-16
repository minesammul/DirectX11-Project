#pragma once
#include "MonsterState.h"

class IronGolemIdleState : public MonsterState
{
private:
	const float PLAYER_FIND_DISTANCE;
	const float PLAYER_ATTACK_DISTANCE;
	const float PLAYER_LOOKAT_ROTATE_DEGREE;

private:
	int findAnimationIndex;

public:
	IronGolemIdleState();
	~IronGolemIdleState();

public:
	static IronGolemIdleState* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
	virtual void Exit(CSSN007MonsterScript * monsterScript) override;
};

