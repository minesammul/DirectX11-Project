#pragma once
#include "MonsterComponent.h"

class MonsterFindPlayer : public MonsterComponent
{
public:
	MonsterFindPlayer();
	~MonsterFindPlayer();

public:
	// MonsterComponent��(��) ���� ��ӵ�
	virtual void Update(CMonsterScript * monster) override;

};

