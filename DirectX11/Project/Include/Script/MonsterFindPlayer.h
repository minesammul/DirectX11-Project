#pragma once
#include "MonsterComponent.h"

class MonsterFindPlayer : public MonsterComponent
{
public:
	MonsterFindPlayer();
	~MonsterFindPlayer();

public:
	// MonsterComponent을(를) 통해 상속됨
	virtual void Update(CMonsterScript * monster) override;

};

