#pragma once
#include "MonsterState.h"
class MonsterAttackState : public MonsterState
{
private:
	CAnimation2D* monsterAnimation;

public:
	MonsterAttackState();
	~MonsterAttackState();

public:
	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CMonsterScript * monster) override;

	virtual void Update(CMonsterScript * monster) override;


	static MonsterAttackState* GetInstance()
	{
		static MonsterAttackState* instance = new MonsterAttackState;
		return instance;
	}
};

