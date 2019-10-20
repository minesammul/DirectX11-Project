#pragma once
#include "MonsterState.h"

class MonsterMoveState : public MonsterState
{
private:
	CAnimation2D* monsterAnimation;

public:
	MonsterMoveState();
	~MonsterMoveState();

public:
	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CMonsterScript * monster) override;
	virtual void Update(CMonsterScript * monster) override;

	static MonsterMoveState* GetInstance()
	{
		static MonsterMoveState* instance = new MonsterMoveState;
		return instance;
	}
};

