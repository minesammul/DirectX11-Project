#include "stdafx.h"
#include "IronGolemOnState.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"

IronGolemOnState::IronGolemOnState()
{
}


IronGolemOnState::~IronGolemOnState()
{
}

IronGolemOnState * IronGolemOnState::GetInstance()
{
	static IronGolemOnState instance;
	return &instance;
}

void IronGolemOnState::Init(CSSN007MonsterScript * monsterScript)
{
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"MonsterOn", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//
}

void IronGolemOnState::Update(CSSN007MonsterScript * monsterScript)
{
	// Animation Done is Init
	bool isAllDoneAnimation = true;
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation()==false)
		{
			isAllDoneAnimation = false;
		}
	}

	if (isAllDoneAnimation == true)
	{
		IronGolemIdleState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemIdleState::GetInstance());
	}
	//
}

void IronGolemOnState::Exit(CSSN007MonsterScript * monsterScript)
{
}
