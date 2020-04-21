#include "stdafx.h"
#include "IronGolemAttack1State.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "SSN008AttackBoxScript.h"
#include "IronGolemDieState.h"
#include "EventQueueMgr.h"

IronGolemAttack1State::IronGolemAttack1State()
{
}


IronGolemAttack1State::~IronGolemAttack1State()
{
}

bool IronGolemAttack1State::CheckIdleState(CSSN007MonsterScript * monsterScript)
{
	float curAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(monsterScript->Object());
	if (curAnimationTimeRatio >= 1.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IronGolemAttack1State * IronGolemAttack1State::GetInstance()
{
	static IronGolemAttack1State instance;
	return &instance;
}

void IronGolemAttack1State::Init(CSSN007MonsterScript * monsterScript)
{
	CFunctionMgr::GetInst()->SetAnimation(monsterScript->Object(), L"Attack01", false);
	monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	monsterScript->GetAttackBoxScript()->SetAttackted(false);

	mIsAttackCollisionStart = false;

	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::EFFECT_THUNDER_ON;
		addEvent.sendObjectName = monsterScript->Object()->GetName();
		addEvent.receiveObjectName = L"IronGolemWeaponMesh";
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}
}

void IronGolemAttack1State::Update(CSSN007MonsterScript * monsterScript)
{
	if (CheckDieState(monsterScript) == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());

		{
			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::EFFECT_THUNDER_OFF;
			addEvent.sendObjectName = monsterScript->Object()->GetName();
			addEvent.receiveObjectName = L"IronGolemWeaponMesh";
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
	}
	else if (CheckIdleState(monsterScript) == true)
	{
		IronGolemIdleState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemIdleState::GetInstance());

		{
			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::EFFECT_THUNDER_OFF;
			addEvent.sendObjectName = monsterScript->Object()->GetName();
			addEvent.receiveObjectName = L"IronGolemWeaponMesh";
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
	}
	else
	{
		SetActiveAttackCollision(monsterScript, 0.4f, 0.6f);
		
		if (monsterScript->GetAttackBoxScript()->GetActiveCollision() == true)
		{
			if (mIsAttackCollisionStart == false)
			{
				mIsAttackCollisionStart = monsterScript->GetAttackBoxScript()->GetActiveCollision();

				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::DECAL_THUNDER_ON;
				addEvent.sendObjectName = monsterScript->Object()->GetName();
				addEvent.receiveObjectName = L"IronGolemAttackDecal";

				Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

				Vec3 monsterFrontVector = monsterScript->Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
				monsterFrontVector *= -1.f;
				monsterFrontVector.Normalize();

				monsterPosition += monsterFrontVector*600.f;
				
				SendData inputData;

				inputData.floatValue = monsterPosition.x;
				addEvent.sendObjectData.push_back(inputData);

				inputData.floatValue = monsterPosition.y;
				addEvent.sendObjectData.push_back(inputData);

				inputData.floatValue = monsterPosition.z;
				addEvent.sendObjectData.push_back(inputData);

				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
		}
	}
}