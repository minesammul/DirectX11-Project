#include "stdafx.h"
#include "IronGolemIdleState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemWalkFrontState.h"
#include "IronGolemAttack1State.h"
#include "IronGolemAttack3State.h"
#include "IronGolemRotateLeftState.h"
#include "IronGolemRotateRightState.h"
#include "IronGolemDieState.h"

IronGolemIdleState::IronGolemIdleState() :
	PLAYER_FIND_DISTANCE(1000.f),
	PLAYER_ATTACK_DISTANCE(500.f),
	PLAYER_LOOKAT_ROTATE_DEGREE(20.f)
{
}


IronGolemIdleState::~IronGolemIdleState()
{
}

IronGolemIdleState * IronGolemIdleState::GetInstance()
{
	static IronGolemIdleState instance;
	return &instance;
}

void IronGolemIdleState::Init(CSSN007MonsterScript * monsterScript)
{
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Idle", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void IronGolemIdleState::Update(CSSN007MonsterScript * monsterScript)
{
	if (monsterScript->GetDead() == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
		return;
	}


	// Animation Done is Init
	bool isAllDoenAnimation = true;
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
		else
		{
			isAllDoenAnimation = false;
		}
	}
	//

	{
		Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
		Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

		Vec3 monsterToPlayerVector = playerPosition - monsterPosition;
		monsterToPlayerVector.Normalize();

		Vec3 monsterFrontVector = monsterScript->Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
		monsterFrontVector *= -1.f;
		monsterFrontVector.Normalize();

		float dotValue = monsterFrontVector.Dot(monsterToPlayerVector);
		float radian = acosf(dotValue);
		float degree = XMConvertToDegrees(radian);

		if (degree > PLAYER_LOOKAT_ROTATE_DEGREE)
		{
			Vec3 crossValue = monsterFrontVector.Cross(monsterToPlayerVector);

			if (crossValue.y > 0.f)
			{
				IronGolemRotateRightState::GetInstance()->Init(monsterScript);
				monsterScript->SetState(IronGolemRotateRightState::GetInstance());
			}
			else
			{
				IronGolemRotateLeftState::GetInstance()->Init(monsterScript);
				monsterScript->SetState(IronGolemRotateLeftState::GetInstance());
			}
		}
	}


	{
		Vec3 playerPosition = monsterScript->GetPlayerObject()->Transform()->GetLocalPos();
		Vec3 monsterPosition = monsterScript->Object()->Transform()->GetLocalPos();

		float monsterToPlayerDistance = Vec3::Distance(playerPosition, monsterPosition);

		if (PLAYER_ATTACK_DISTANCE < monsterToPlayerDistance && monsterToPlayerDistance < PLAYER_FIND_DISTANCE)
		{
			if (isAllDoenAnimation == true)
			{
				IronGolemWalkFrontState::GetInstance()->Init(monsterScript);
				monsterScript->SetState(IronGolemWalkFrontState::GetInstance());
			}
		}
		else if (monsterToPlayerDistance < PLAYER_ATTACK_DISTANCE)
		{
			if (isAllDoenAnimation == true)
			{
				srand(time(0));
				int attackType = rand() % 10;

				if (attackType < 5)
				{
					IronGolemAttack1State::GetInstance()->Init(monsterScript);
					monsterScript->SetState(IronGolemAttack1State::GetInstance());
				}
				else
				{
					IronGolemAttack3State::GetInstance()->Init(monsterScript);
					monsterScript->SetState(IronGolemAttack3State::GetInstance());
				}
			}
		}
	}
}

void IronGolemIdleState::Exit(CSSN007MonsterScript * monsterScript)
{
}
