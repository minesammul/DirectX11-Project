#include "stdafx.h"
#include "MonsterScript.h"

#include "MonsterState.h"
#include "MonsterIdleState.h"
#include "MonsterAttackState.h"
#include "MonsterMoveState.h"

#include "MonsterMove.h"
#include "MonsterAttack.h"



CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
	this->monsterIdleState = new MonsterIdleState;
	this->monsterAttackState = new MonsterAttackState;
	this->monsterMoveState = new MonsterMoveState;

	monsterState = monsterIdleState;
	
	for (int componentIndex = 0; componentIndex < (UINT)MONSTER_COMPONENT::END; componentIndex++)
	{
		if (componentIndex == (UINT)MONSTER_COMPONENT::MOVE)
		{
			monsterComponent[componentIndex] = new MonsterMove;
			monsterComponent[componentIndex]->SetMonster(this);
		}
		else if (componentIndex == (UINT)MONSTER_COMPONENT::ATTACK)
		{
			monsterComponent[componentIndex] = new MonsterAttack;
			monsterComponent[componentIndex]->SetMonster(this);
		}
		else
		{
			//추가되는 Component가 존재하면 이에 대한 작업을 해야한다.
			assert(false);
		}

	}
}

CMonsterScript::~CMonsterScript()
{
	delete monsterIdleState;
	delete monsterAttackState;
	delete monsterMoveState;

	for (int index = 0; index < (UINT)MONSTER_COMPONENT::END; index++)
	{
		if (monsterComponent[index] != nullptr)
		{
			delete monsterComponent[index];
			monsterComponent[index] = nullptr;
		}
	}
}

void CMonsterScript::start()
{
	monsterState->Init(this);
}

void CMonsterScript::update()
{
	monsterState->Update(this);
}

MonsterMove * CMonsterScript::GetMonsterMove(void)
{
	return dynamic_cast<MonsterMove*>(monsterComponent[(UINT)MONSTER_COMPONENT::MOVE]);
}

MonsterAttack * CMonsterScript::GetMonsterAttack(void)
{
	return dynamic_cast<MonsterAttack*>(monsterComponent[(UINT)MONSTER_COMPONENT::ATTACK]);
}
