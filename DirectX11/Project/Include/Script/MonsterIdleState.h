#pragma once
#include "MonsterState.h"

class MonsterIdleState : public MonsterState
{
private:
	int findAnimationIndex;


public:
	MonsterIdleState();
	~MonsterIdleState();

public:
	static MonsterIdleState* GetInstance();

	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
	virtual void Exit(CSSN007MonsterScript * monsterScript) override;
};

