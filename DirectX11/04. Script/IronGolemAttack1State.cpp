#include "stdafx.h"
#include "IronGolemAttack1State.h"

#include "SSN007MonsterScript.h"
#include "IronGolemIdleState.h"
#include "SSN008AttackBoxScript.h"

IronGolemAttack1State::IronGolemAttack1State()
{
}


IronGolemAttack1State::~IronGolemAttack1State()
{
}

IronGolemAttack1State * IronGolemAttack1State::GetInstance()
{
	static IronGolemAttack1State instance;
	return &instance;
}

void IronGolemAttack1State::Init(CSSN007MonsterScript * monsterScript)
{
	//Animation Init
	for (int index = 0; index < monsterScript->Object()->GetChild().size(); index++)
	{
		if (monsterScript->Object()->GetChild()[index]->Animator3D() == nullptr)
		{
			continue;
		}

		if (monsterScript->Object()->GetChild()[index]->Animator3D()->FindAnimClipIndex(L"Attack01", findAnimationIndex) == false)
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

void IronGolemAttack1State::Update(CSSN007MonsterScript * monsterScript)
{
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

	if (animationRatio > 0.4f)
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

void IronGolemAttack1State::Exit(CSSN007MonsterScript * monsterScript)
{
}