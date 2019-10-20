#include "stdafx.h"
#include "MonsterAttackState.h"


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
}

void MonsterAttackState::Update(CMonsterScript * monster)
{
	if (monsterAnimation->IsPlay() == false)
	{
		monsterAnimation->Play();
	}
}
