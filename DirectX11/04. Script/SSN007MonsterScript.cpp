#include "stdafx.h"
#include "SSN007MonsterScript.h"

#include "IronGolemStandState.h"
#include "FunctionMgr.h"
#include "SSN008AttackBoxScript.h"

CSSN007MonsterScript::CSSN007MonsterScript() :
	CScript((UINT)SCRIPT_TYPE::SSN007MONSTERSCRIPT),
	MONSTER_MOVE_SPEED(300.f),
	MONSTER_ROTATE_SPEED(25.f)
{

}


CSSN007MonsterScript::~CSSN007MonsterScript()
{
}

void CSSN007MonsterScript::CheckHited()
{
	if (mIsHit == true)
	{
		mIsHit = false;
	}
}

void CSSN007MonsterScript::CheckDie()
{
	if (mMonsterHP <= 0)
	{
		mIsDead = true;
	}
}

void CSSN007MonsterScript::start()
{
	mPlayerObject = CFunctionMgr::GetInst()->FindObject(L"Player");
	

	CGameObject* attackBox = CFunctionMgr::GetInst()->FindObjectInChildUseLayer(Object(), L"AttackBox");
	mAttackBoxScript = dynamic_cast<CSSN008AttackBoxScript*>(CFunctionMgr::GetInst()->FindScript(attackBox->GetName(), SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT));


	mMonsterHP = 2;

	mIsHit = false;
	mIsDead = false;


	mMonsterState = IronGolemStandState::GetInstance();
	mMonsterState->Init(this);
}

void CSSN007MonsterScript::update()
{
	CheckHited();

	CheckDie();

	mMonsterState->Update(this);
}

void CSSN007MonsterScript::SetState(MonsterState * state)
{
	mMonsterState = state;
}

CGameObject * CSSN007MonsterScript::GetPlayerObject()
{
	return mPlayerObject;
}

CSSN008AttackBoxScript * CSSN007MonsterScript::GetAttackBoxScript()
{
	return mAttackBoxScript;
}
