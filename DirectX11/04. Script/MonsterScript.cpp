#include "stdafx.h"
#include "MonsterScript.h"

#include "MonsterState.h"
#include "MonsterIdleState.h"
#include "MonsterAttackState.h"
#include "MonsterMoveState.h"

#include "MonsterMove.h"



CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
	this->monsterIdleState = new MonsterIdleState;
	this->monsterAttackState = new MonsterAttackState;
	this->monsterMoveState = new MonsterMoveState;

	monsterState = monsterIdleState;
	
	monsterComponent[(UINT)MONSTER_COMPONENT::MOVE] = new MonsterMove;
	monsterComponent[(UINT)MONSTER_COMPONENT::MOVE]->SetMonster(this);
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
