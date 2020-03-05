#include "stdafx.h"
#include "PlayerWalkLeftState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollLeftState.h"
#include "PlayerAttack1State.h"
#include "PlayerHealSuccessState.h"
#include "PlayerHitedState.h"
#include "PlayerDeadState.h"
#include "FunctionMgr.h"

PlayerWalkLeftState::PlayerWalkLeftState()
{
}


PlayerWalkLeftState::~PlayerWalkLeftState()
{
}

PlayerWalkLeftState * PlayerWalkLeftState::GetInstance()
{
	static PlayerWalkLeftState instance;

	return &instance;
}

void PlayerWalkLeftState::Init(CSSN002PlayerScript * playerScript)
{	
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Walk_Left", true);
}

void PlayerWalkLeftState::Update(CSSN002PlayerScript * playerScript)
{
	playerScript->RestoreSP();

	if (playerScript->GetDead() == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}

	if (playerScript->GetHit() == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
	}

	if (KEYHOLD(KEY_TYPE::KEY_A))
	{
		if (playerScript->GetPlayerMovable() == false)
		{
			Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
			playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
			return;
		}

		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MainCamera", findObject);

		Vec3 walkDirection = findObject[0]->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
		walkDirection *= -1.f;
		walkDirection.y = 0.f;

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerMoveSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}
	else if (KEYAWAY(KEY_TYPE::KEY_A))
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		if (playerScript->CanUseSP(PlayerRollLeftState::GetInstance()->GetUseSPAmount()) == true)
		{
			PlayerRollLeftState::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerRollLeftState::GetInstance());
		}
	}

	if (KEYTAB(KEY_TYPE::KEY_LBTN))
	{
		if (playerScript->CanUseSP(PlayerAttack1State::GetInstance()->GetUseSPAmount()) == true)
		{
			PlayerAttack1State::GetInstance()->Init(playerScript);
			playerScript->SetState(PlayerAttack1State::GetInstance());
		}
	}

	if (KEYTAB(KEY_TYPE::KEY_E))
	{
		PlayerHealSuccessState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealSuccessState::GetInstance());
	}
}
