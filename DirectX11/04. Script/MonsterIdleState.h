#pragma once
#include "MonsterState.h"
class MonsterIdleState : public MonsterState
{
private:
	CAnimation2D* monsterAnimation;


public:
	MonsterIdleState();
	~MonsterIdleState();


public:
	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CMonsterScript * monster) override;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Update(CMonsterScript * monster) override;

	static MonsterIdleState* GetInstance()
	{
		static MonsterIdleState* instance = new MonsterIdleState;
		return instance;
	}


};

