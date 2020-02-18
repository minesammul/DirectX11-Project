#pragma once
#include <Script.h>
#include "MonsterState.h"

class CSSN007MonsterScript : public CScript
{
private:
	MonsterState* monsterState;

	CGameObject* playerObject;

	CScript* attackBoxScript;

	bool isHit;

	int monsterHP;

	bool isDead;

public:
	CSSN007MonsterScript();
	~CSSN007MonsterScript();

public:
	virtual void start();
	virtual void update();

	void SetState(MonsterState* state);
	CGameObject* GetPlayerObject();
	CScript* GetAttackBoxScript();

	void SetHit(bool hit) { isHit = hit; }
	bool GetHit() { return isHit; }

	bool GetDead() { return isDead; }

	int GetMonsterHP() { return monsterHP; }
};

