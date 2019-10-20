#include "stdafx.h"
#include "MonsterIdleState.h"
#include "MonsterAttackState.h"
#include "MonsterMoveState.h"

MonsterIdleState::MonsterIdleState()
{
}


MonsterIdleState::~MonsterIdleState()
{
}


void MonsterIdleState::Init(CMonsterScript * monster)
{
	map<wstring, CAnimation2D*> monsterAnimationList = monster->Object()->Animator2D()->GetAnimList();
	map<wstring, CAnimation2D*>::const_iterator curMonsterAnimation = monsterAnimationList.begin();
	
	monsterAnimation = nullptr;
	int animationKeyIndex = 0;
	while (curMonsterAnimation != monsterAnimationList.end())
	{
		const wchar_t* animationName = curMonsterAnimation->first.c_str();
		const wchar_t* subStr = L"Idle";
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


void MonsterIdleState::Update(CMonsterScript * monster)
{
	if (monsterAnimation->IsPlay() == false)
	{
		monsterAnimation->Play();
	}

	vector<CGameObject*> player;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", player);

	Vec3 playerPosition = player[0]->Transform()->GetLocalPos();

	Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

	Vec3 distance = XMVector2Length(playerPosition - monsterPosition);

	if (distance.x < 200.f)
	{
		monster->GetMonsterMoveState()->Init(monster);
		monster->SetMonsterState(monster->GetMonsterMoveState());
	}
	
}

