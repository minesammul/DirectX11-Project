#pragma once
#include "MonsterState.h"

class IronGolemWalkFrontState : public MonsterState
{
private:
	const float PLAYER_FIND_DISTANCE;
	const float WALK_SPEED;

private:
	int findAnimationIndex;

public:
	IronGolemWalkFrontState();
	~IronGolemWalkFrontState();

public:
	static IronGolemWalkFrontState* GetInstance();

	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
	virtual void Exit(CSSN007MonsterScript * monsterScript) override;
};

