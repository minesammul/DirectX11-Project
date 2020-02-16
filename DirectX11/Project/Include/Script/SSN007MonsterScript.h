#pragma once
#include <Script.h>
#include "MonsterState.h"

class CSSN007MonsterScript : public CScript
{
private:
	MonsterState* monsterState;

	CGameObject* playerObject;

	CScript* attackBoxScript;

public:
	CSSN007MonsterScript();
	~CSSN007MonsterScript();

public:
	virtual void start();
	virtual void update();

	void SetState(MonsterState* state);
	CGameObject* GetPlayerObject();
	CScript* GetAttackBoxScript();
};

