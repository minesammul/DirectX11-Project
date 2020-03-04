#include "stdafx.h"
#include "PlayerWalkFrontState.h"

#include "SSN002PlayerScript.h"
#include "PlayerIdleState.h"
#include "PlayerRollFrontState.h"
#include "PlayerAttack1State.h"
#include "PlayerHealSuccessState.h"
#include "PlayerDeadState.h"
#include "PlayerHitedState.h"
#include "FunctionMgr.h"
#include <Camera.h>

PlayerWalkFrontState::PlayerWalkFrontState()
{
}


PlayerWalkFrontState::~PlayerWalkFrontState()
{
}

bool PlayerWalkFrontState::CheckDieState(CSSN002PlayerScript * playerScript)
{
	return playerScript->GetDead();
}

bool PlayerWalkFrontState::CheckHitedState(CSSN002PlayerScript * playerScript)
{
	return playerScript->GetHit();
}

bool PlayerWalkFrontState::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	return KEYAWAY(KEY_TYPE::KEY_W);
}

bool PlayerWalkFrontState::CheckRollFrontState(CSSN002PlayerScript * playerScript)
{
	return (KEYTAB(KEY_TYPE::KEY_SPACE) && playerScript->CanUseSP(PlayerRollFrontState::GetInstance()->GetUseSPAmount()) == true);
}

bool PlayerWalkFrontState::CheckAttack1State(CSSN002PlayerScript * playerScript)
{
	return (KEYTAB(KEY_TYPE::KEY_LBTN) && playerScript->CanUseSP(PlayerAttack1State::GetInstance()->GetUseSPAmount()) == true);
}

bool PlayerWalkFrontState::CheckHealState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_E);
}

PlayerWalkFrontState * PlayerWalkFrontState::GetInstance()
{
	static PlayerWalkFrontState instance;
	return &instance;
}

void PlayerWalkFrontState::Init(CSSN002PlayerScript * playerScript)
{
	CFunctionMgr::GetInst()->SetAnimation(playerScript->Object(), L"Walk_Front", true);
}

void PlayerWalkFrontState::Update(CSSN002PlayerScript * playerScript)
{
	if (CheckDieState(playerScript) == true)
	{
		PlayerDeadState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerDeadState::GetInstance());
	}
	else if (CheckHitedState(playerScript) == true)
	{
		PlayerHitedState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHitedState::GetInstance());
	}
	else if (CheckIdleState(playerScript) == true)
	{
		PlayerIdleState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerIdleState::GetInstance());
	}
	else if (CheckRollFrontState(playerScript) == true)
	{
		PlayerRollFrontState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerRollFrontState::GetInstance());
	}
	else if (CheckAttack1State(playerScript) == true)
	{
		PlayerAttack1State::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerAttack1State::GetInstance());
	}
	else if (CheckHealState(playerScript) == true)
	{
		PlayerHealSuccessState::GetInstance()->Init(playerScript);
		playerScript->SetState(PlayerHealSuccessState::GetInstance());
	}
	else
	{
		playerScript->RestoreSP();

		if (playerScript->GetPlayerMovable() == false)
		{
			Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
			playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
			return;
		}

		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MainCamera", findObject);

		Vec3 walkDirection = findObject[0]->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
		walkDirection.y = 0.f;

		Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
		playerPosition += walkDirection * playerScript->GetPlayerMoveSpeed();
		playerScript->Object()->Transform()->SetLocalPos(playerPosition);
	}
}
