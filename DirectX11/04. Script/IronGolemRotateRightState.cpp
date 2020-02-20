#include "stdafx.h"
#include "IronGolemRotateRightState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "IronGolemDieState.h"

IronGolemRotateRightState::IronGolemRotateRightState()
{
}


IronGolemRotateRightState::~IronGolemRotateRightState()
{
}

IronGolemRotateRightState * IronGolemRotateRightState::GetInstance()
{
	static IronGolemRotateRightState instance;
	return &instance;
}

void IronGolemRotateRightState::Init(CSSN007MonsterScript * monsterScript)
{
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Rotate_Right", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void IronGolemRotateRightState::Update(CSSN007MonsterScript * monsterScript)
{
	if (monsterScript->GetDead() == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
		return;
	}

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

		Vec3 monsterToPlayerVector = playerPosition - monsterPosition;
		monsterToPlayerVector.Normalize();

		Vec3 monsterFrontVector = monsterScript->Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
		monsterFrontVector *= -1.f;
		monsterFrontVector.Normalize();

		float dotValue = monsterFrontVector.Dot(monsterToPlayerVector);
		float radian = acosf(dotValue);
		float degree = XMConvertToDegrees(radian);

		if (degree > 10.f)
		{
			Vec3 mosnterRotate = monsterScript->Object()->Transform()->GetLocalRot();
			mosnterRotate.y += GetRadian(monsterScript->GetMonsterRotateSpeed());
			monsterScript->Object()->Transform()->SetLocalRot(mosnterRotate);
		}
		else
		{
			IronGolemIdleState::GetInstance()->Init(monsterScript);
			monsterScript->SetState(IronGolemIdleState::GetInstance());
		}
	}
}

void IronGolemRotateRightState::Exit(CSSN007MonsterScript * monsterScript)
{
}
