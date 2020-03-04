#include "stdafx.h"
#include "IronGolemWalkFrontState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "IronGolemDieState.h"

IronGolemWalkFrontState::IronGolemWalkFrontState():
	PLAYER_FIND_DISTANCE(200.f)
{
}


IronGolemWalkFrontState::~IronGolemWalkFrontState()
{
}

IronGolemWalkFrontState * IronGolemWalkFrontState::GetInstance()
{
	static IronGolemWalkFrontState instance;
	return &instance;
}

void IronGolemWalkFrontState::Init(CSSN007MonsterScript * monsterScript)
{
	if (monsterScript->GetDead() == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
		return;
	}

	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Walk_Front", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void IronGolemWalkFrontState::Update(CSSN007MonsterScript * monsterScript)
{
	// Animation Done is Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation())
		{
			monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
			monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
		}
	}

	{
		Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
		Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

		float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

		if (monsterToPlayerDistance < PLAYER_FIND_DISTANCE)
		{
			IronGolemIdleState::GetInstance()->Init(monsterScript);
			monsterScript->SetState(IronGolemIdleState::GetInstance());
		}
		else
		{
			Vec3 monsterWalkDirection = playerPosition - monsterPosition;
			monsterWalkDirection.Normalize();

			Vec3 monsterLookAtDirection = monsterWalkDirection;
			monsterScript->Object()->Transform()->SetLookAt(monsterLookAtDirection);

			monsterPosition += monsterScript->GetMonsterMoveSpeed() * monsterWalkDirection;
			monsterScript->Object()->Transform()->SetLocalPos(monsterPosition);

			float radianValue = GetRadian(270.f);
			Vec3 monsterRoatate = monsterScript->Object()->Transform()->GetLocalRot();
			monsterRoatate.x = radianValue;
			monsterScript->Object()->Transform()->SetLocalRot(monsterRoatate);
		}
	}
	//
}