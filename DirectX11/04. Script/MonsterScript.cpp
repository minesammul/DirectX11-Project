#include "stdafx.h"
#include "MonsterScript.h"

#include "MonsterState.h"
#include "MonsterIdleState.h"
#include "MonsterAttackState.h"
#include "MonsterMoveState.h"

#include "MonsterMove.h"
#include "MonsterAttack.h"

#include "AttackBoxScript.h"


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
			//�߰��Ǵ� Component�� �����ϸ� �̿� ���� �۾��� �ؾ��Ѵ�.
			assert(false);
		}

	}

	hp = 10;
	isDie = false;
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

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\DieEffect.pref", L"Prefab\\DieEffect.pref");
	dieEffectPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\DieEffect.pref");
}

void CMonsterScript::update()
{
	monsterState->Update(this);

	if (isDie == false)
	{
		if (hp <= 0)
		{
			map<UINT, CScript*> prefabInputScripts;

			vector<UINT> prefabScriptTypes = dieEffectPrefab->GetScriptType();
			vector<wstring> allScriptInfo;
			CScriptMgr::GetScriptInfo(allScriptInfo);

			for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
			{
				UINT scriptType = prefabScriptTypes[scriptIndex];
				wstring scriptName = allScriptInfo[scriptType];
				CScript* prefabScript = CScriptMgr::GetScript(scriptName);
				prefabInputScripts[scriptType] = prefabScript;
			}

			Vec3 dieEffectPosition = Object()->Transform()->GetLocalPos();

			Instantiate(dieEffectPrefab, dieEffectPosition, prefabInputScripts);

			isDie = true;

			Object()->Active(false);
		}

		{
			vector<CGameObject*> childObject = Object()->GetChild();
			if (childObject.empty() == false)
			{
				for (int index = 0; index < childObject.size(); index++)
				{
					wstring attackBoxName = Object()->GetName();
					attackBoxName += L"AttackBox";
					if (childObject[index]->GetName().compare(attackBoxName) == 0)
					{
						if(monsterDirection.x>0)
						{ 
							Vec3 attackBoxPosition = childObject[index]->Transform()->GetLocalPos();
							if (attackBoxPosition.x < 0)
							{
								attackBoxPosition.x *= -1;
								childObject[index]->Transform()->SetLocalPos(attackBoxPosition);
							}
						}
						else
						{
							Vec3 attackBoxPosition = childObject[index]->Transform()->GetLocalPos();
							if (attackBoxPosition.x > 0)
							{
								attackBoxPosition.x *= -1;
								childObject[index]->Transform()->SetLocalPos(attackBoxPosition);
							}
						}

						break;
					}
				}
			}
		}
	}
}

MonsterMove * CMonsterScript::GetMonsterMove(void)
{
	return dynamic_cast<MonsterMove*>(monsterComponent[(UINT)MONSTER_COMPONENT::MOVE]);
}

MonsterAttack * CMonsterScript::GetMonsterAttack(void)
{
	return dynamic_cast<MonsterAttack*>(monsterComponent[(UINT)MONSTER_COMPONENT::ATTACK]);
}

void CMonsterScript::SetMonsterLeftRightImage(int OriginZeroInverseOne)
{
	m_pCloneMtrl = Object()->MeshRender()->GetCloneMaterial();
	m_pCloneMtrl->SetData(SHADER_PARAM::INT_0, &OriginZeroInverseOne);
}

void CMonsterScript::SetMonsterDirectionImage(void)
{
	vector<CGameObject*> player;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", player);
	Vec3 playerPosition = player[0]->Transform()->GetLocalPos();
	Vec3 monsterPosition = Object()->Transform()->GetLocalPos();
	Vec3 monsterDirection = playerPosition - monsterPosition;
	monsterDirection = XMVector2Normalize(monsterDirection);
	if (monsterDirection.x > 0)
	{
		SetMonsterLeftRightImage(0);
	}
	else
	{
		SetMonsterLeftRightImage(1);
	}

	this->monsterDirection = monsterDirection;
}
