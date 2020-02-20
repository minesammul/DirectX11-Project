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

		playerObject = findPlayer[0];
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
				attackBoxScript = attackBox->GetScripts()[index];
				break;
			}
		}
	}

	isHit = false;
	monsterHP = 2;
	isDead = false;

	{
		monsterState = IronGolemStandState::GetInstance();
		monsterState->Init(this);
	}
}

void CSSN007MonsterScript::update()
{
	if (isHit == true)
	{
		isHit = false;
	}

	if (monsterHP <= 0)
	{
		isDead = true;
	}


	monsterState->Update(this);
}

void CSSN007MonsterScript::SetState(MonsterState * state)
{
	monsterState = state;
}

CGameObject * CSSN007MonsterScript::GetPlayerObject()
{
	return playerObject;
}

CScript * CSSN007MonsterScript::GetAttackBoxScript()
{
	return attackBoxScript;
}
