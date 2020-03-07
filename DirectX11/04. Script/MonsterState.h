#pragma once
#include <Animator3D.h>
#include "FunctionMgr.h"

class CSSN007MonsterScript;
class MonsterState
{
public:
	MonsterState();
	~MonsterState();

protected:
	bool CheckDieState(CSSN007MonsterScript* monsterScript);

	virtual bool CheckIdleState(CSSN007MonsterScript* monsterScript);
	
	bool CheckRotateLeftState(CSSN007MonsterScript* monsterScript, float rotateStartRadian);
	bool CheckRotateRightState(CSSN007MonsterScript* monsterScript, float rotateStartRadian);

	void SetActiveAttackCollision(CSSN007MonsterScript * monsterScript, float startActiveTimeRatio, float endActiveTimeRatio);

public:
	virtual void Init(CSSN007MonsterScript* monsterScript) = 0;
	virtual void Update(CSSN007MonsterScript* monsterScript) = 0;
};

