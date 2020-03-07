#pragma once
#include "MonsterState.h"

class IronGolemAttack1State : public MonsterState
{
public:
	IronGolemAttack1State();
	~IronGolemAttack1State();

private:
	virtual bool CheckIdleState(CSSN007MonsterScript * monsterScript);

public:
	static IronGolemAttack1State* GetInstance();

	// MonsterState��(��) ���� ��ӵ�
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

