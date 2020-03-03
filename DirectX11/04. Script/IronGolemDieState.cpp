#include "stdafx.h"
#include "IronGolemDieState.h"

#include "SSN007MonsterScript.h"
#include "SSN008AttackBoxScript.h"

IronGolemDieState::IronGolemDieState()
{
}


IronGolemDieState::~IronGolemDieState()
{
}

IronGolemDieState * IronGolemDieState::GetInstance()
{
	static IronGolemDieState instance;
	return &instance;
}

void IronGolemDieState::Init(CSSN007MonsterScript * monsterScript)
{
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Dead", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//

	monsterScript->GetAttackBoxScript()->SetActiveCollision(false);
	monsterScript->GetAttackBoxScript()->SetAttackted(false);
}

void IronGolemDieState::Update(CSSN007MonsterScript * monsterScript)
{
}

void IronGolemDieState::Exit(CSSN007MonsterScript * monsterScript)
{
}
