#include "stdafx.h"
#include "MonsterAttackState.h"

#include "MonsterIdleState.h"

#include "MonsterAttack.h"

#include "MonsterAttackStrategy.h"
#include "MonsterCircleWaveBullet.h"

MonsterAttackState::MonsterAttackState()
{
}


MonsterAttackState::~MonsterAttackState()
{
}

void MonsterAttackState::Init(CMonsterScript * monster)
{
	map<wstring, CAnimation2D*> monsterAnimationList = monster->Object()->Animator2D()->GetAnimList();
	map<wstring, CAnimation2D*>::const_iterator curMonsterAnimation = monsterAnimationList.begin();

	monsterAnimation = nullptr;
	int animationKeyIndex = 0;
	while (curMonsterAnimation != monsterAnimationList.end())
	{
		const wchar_t* animationName = curMonsterAnimation->first.c_str();
		const wchar_t* subStr = L"Attack";
		const wchar_t* tokStr = wcsstr(animationName, subStr);

		if (tokStr != nullptr)
		{
			monsterAnimation = curMonsterAnimation->second;
			monster->Object()->Animator2D()->SetCurAnim(monsterAnimation);
			break;
		}

		curMonsterAnimation++;
	}

	if (monsterAnimation->IsPlay() == false)
	{
		monsterAnimation->Play();
	}

	monster->GetMonsterAttack()->Init();
	monster->GetMonsterAttack()->GetAttackStrategy()->SetIsAttack(false);
}

void MonsterAttackState::Update(CMonsterScript * monster)
{
	if (monster->GetMonsterAttack()->GetAttackStrategy()->GetIsAttack() == false)
	{
		monster->GetMonsterAttack()->Update(monster);
	}
	
	if(monster->GetMonsterAttack()->GetAttackStrategy()->GetIsAttack() == true &&
		monsterAnimation->IsFinish() == true)
	{
		monster->GetMonsterIdleState()->Init(monster);
		monster->SetMonsterState(monster->GetMonsterIdleState());
	}
}
