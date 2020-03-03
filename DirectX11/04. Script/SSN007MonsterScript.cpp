#include "stdafx.h"
#include "SSN007MonsterScript.h"

#include "IronGolemStandState.h"

CSSN007MonsterScript::CSSN007MonsterScript() :
	CScript((UINT)SCRIPT_TYPE::SSN007MONSTERSCRIPT),
	MONSTER_MOVE_SPEED(300.f),
	MONSTER_ROTATE_SPEED(25.f)
{
}


CSSN007MonsterScript::~CSSN007MonsterScript()
{
}

void CSSN007MonsterScript::start()
{
	{
		vector<CGameObject*> findPlayer;
		CSceneMgr::GetInst()->FindGameObject(L"Player", findPlayer);
		if (findPlayer.empty() == true)
		{
			assert(false && L"Monster Not Find Player");
		}

		mPlayerObject = findPlayer[0];
	}

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

		for (int index = 0; index < attackBox->GetScripts().size(); index++)
		{
			if (attackBox->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT)
			{
				mAttackBoxScript = attackBox->GetScripts()[index];
				break;
			}
		}
	}

	mIsHit = false;
	mMonsterHP = 2;
	mIsDead = false;

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

CScript * CSSN007MonsterScript::GetAttackBoxScript()
{
	return mAttackBoxScript;
}
