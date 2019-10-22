#pragma once
#include <Script.h>

class MonsterState;
class MonsterIdleState;
class MonsterAttackState;
class MonsterMoveState;

class MonsterComponent;
class MonsterMove;
class MonsterAttack;

enum class MONSTER_COMPONENT
{
	MOVE,
	ATTACK,
	END
};

class CMonsterScript :
	public CScript
{
private:
	MonsterState* monsterState;
	MonsterIdleState* monsterIdleState;
	MonsterAttackState* monsterAttackState;
	MonsterMoveState* monsterMoveState;

	MonsterComponent* monsterComponent[(UINT)MONSTER_COMPONENT::END];

public:
	CLONE(CMonsterScript);

public:
	CMonsterScript();
	virtual ~CMonsterScript();

public:
	virtual void start();
	virtual void update();

	MonsterMove* GetMonsterMove(void);
	MonsterAttack* GetMonsterAttack(void);

	void SetMonsterState(MonsterState* state) { monsterState = state; }
	MonsterIdleState* GetMonsterIdleState(void) { return this->monsterIdleState; }
	MonsterAttackState* GetMonsterAttackState(void) { return this->monsterAttackState; }
	MonsterMoveState* GetMonsterMoveState(void) { return this->monsterMoveState; }
};

