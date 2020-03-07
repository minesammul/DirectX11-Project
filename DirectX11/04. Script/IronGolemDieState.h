#pragma once
#include "MonsterState.h"

class IronGolemDieState : public MonsterState
{
public:
	IronGolemDieState();
	~IronGolemDieState();

public:
	static IronGolemDieState* GetInstance();

	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

