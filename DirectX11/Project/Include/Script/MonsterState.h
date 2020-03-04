#pragma once
#include <Animator3D.h>
class CSSN007MonsterScript;

class MonsterState
{
public:
	MonsterState();
	~MonsterState();

public:
	virtual void Init(CSSN007MonsterScript* monsterScript) = 0;
	virtual void Update(CSSN007MonsterScript* monsterScript) = 0;
};

