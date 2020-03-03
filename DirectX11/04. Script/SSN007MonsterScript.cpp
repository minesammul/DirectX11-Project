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
	mMonsterHP = 2;

	mIsHit = false;
	mIsDead = false;
}


CSSN007MonsterScript::~CSSN007MonsterScript()
{
}

void CSSN007MonsterScript::start()
{
	mPlayerObject = CFunctionMgr::GetInst()->FindObject(L"Player");
	

	{
		CGameObject* attackBox = nullptr;
		for (int index = 0; index < Object()->GetChild().size(); index++)
		{
			CLayer* attackBoxLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"AttackBox");
			if (Object()->GetChild()[index]->GetLayerIdx() == attackBoxLayer->GetLayerIdx())
			{
				attackBox = Object()->GetChild()[index];
				break;
			}
		}

		mAttackBoxScript = dynamic_cast<CSSN008AttackBoxScript*>(CFunctionMgr::GetInst()->FindScript(attackBox->GetName(), SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT));
	}



	{
		mMonsterState = IronGolemStandState::GetInstance();
		mMonsterState->Init(this);
	}
}

void CSSN007MonsterScript::update()
{
	if (mIsHit == true)
	{
		mIsHit = false;
	}

	if (mMonsterHP <= 0)
	{
		mIsDead = true;
	}


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
