#pragma once
#include "MonsterState.h"

class IronGolemAttack3State : public MonsterState
{
public:
	IronGolemAttack3State();
	~IronGolemAttack3State();

private:
	virtual bool CheckIdleState(CSSN007MonsterScript * monsterScript);

public:
	static IronGolemAttack3State* GetInstance();

	// MonsterState을(를) 통해 상속됨
	virtual void Init(CSSN007MonsterScript * monsterScript) override;
	virtual void Update(CSSN007MonsterScript * monsterScript) override;
};

