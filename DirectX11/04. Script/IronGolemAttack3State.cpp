#include "stdafx.h"
#include "IronGolemAttack3State.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "SSN008AttackBoxScript.h"
#include "IronGolemDieState.h"

IronGolemAttack3State::IronGolemAttack3State()
{
}


IronGolemAttack3State::~IronGolemAttack3State()
{
}

IronGolemAttack3State * IronGolemAttack3State::GetInstance()
{
	static IronGolemAttack3State instance;
	return &instance;
}

void IronGolemAttack3State::Init(CSSN007MonsterScript * monsterScript)
{
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack03", findAnimationIndex) == false)
		{
			assert(false && L"Not Find Animation");
		}

		monsterScript->Object()->GetChild()[index]->Animator3D()->SetClipTime(findAnimationIndex, 0.f);
		monsterScript->Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(findAnimationIndex);
	}
	//


	((CSSN008AttackBoxScript*)monsterScript->GetAttackBoxScript())->SetActiveCollision(false);
	((CSSN008AttackBoxScript*)monsterScript->GetAttackBoxScript())->SetAttackted(false);
}

void IronGolemAttack3State::Update(CSSN007MonsterScript * monsterScript)
{
	if (monsterScript->GetDead() == true)
	{
		IronGolemDieState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemDieState::GetInstance());
		return;
	}

	// Animation Done is Init
	bool isAllDoneAnimation = true;
	float animationRatio = 0.f;
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->IsDoneAnimation() == false)
		{
			isAllDoneAnimation = false;
			animationRatio = monsterScript->Object()->GetChild()[index]->Animator3D()->GetCurRatioAnimTime();
		}
	}

	if (animationRatio > 0.5f)
	{
		((CSSN008AttackBoxScript*)monsterScript->GetAttackBoxScript())->SetActiveCollision(true);
	}

	if (isAllDoneAnimation == true)
	{
		((CSSN008AttackBoxScript*)monsterScript->GetAttackBoxScript())->SetActiveCollision(false);
		IronGolemIdleState::GetInstance()->Init(monsterScript);
		monsterScript->SetState(IronGolemIdleState::GetInstance());
	}
	//
}

void IronGolemAttack3State::Exit(CSSN007MonsterScript * monsterScript)
{
}
