#include "stdafx.h"
#include "PlayerState.h"
#include "SSN002PlayerScript.h"
#include "SSN008AttackBoxScript.h"


PlayerState::PlayerState() : 
	mUseSPAmount(0)
{
}


PlayerState::~PlayerState()
{
}

bool PlayerState::CheckDieState(CSSN002PlayerScript* playerScript)
{
	return playerScript->GetDead();
}

bool PlayerState::CheckHitedState(CSSN002PlayerScript * playerScript)
{
	return playerScript->GetHit();
}

bool PlayerState::CheckIdleState(CSSN002PlayerScript * playerScript)
{
	return false;
}

bool PlayerState::CheckWalkFrontState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_W);
}

bool PlayerState::CheckWalkBackState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_S);
}

bool PlayerState::CheckWalkLeftState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_A);
}

bool PlayerState::CheckWalkRightState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_D);
}

bool PlayerState::CheckRollState(CSSN002PlayerScript * playerScript, int useSP)
{
	return (KEYTAB(KEY_TYPE::KEY_SPACE) && playerScript->CanUseSP(useSP) == true);
}

bool PlayerState::CheckHealState(CSSN002PlayerScript * playerScript)
{
	return KEYTAB(KEY_TYPE::KEY_E);
}


bool PlayerState::CheckAttackState(CSSN002PlayerScript * playerScript, int useSP, float nextAttackStartTimeRatio, float nextAttackEndTimeRatio, bool* isNextAttack)
{
	if (isNextAttack == nullptr)
	{
		return (KEYTAB(KEY_TYPE::KEY_LBTN) && playerScript->CanUseSP(useSP) == true);
	}
	else
	{
		float nowAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());

		if (*isNextAttack == false)
		{
			if (nextAttackStartTimeRatio <= nowAnimationTimeRatio && nowAnimationTimeRatio <= nextAttackEndTimeRatio)
			{
				if (KEYTAB(KEY_TYPE::KEY_LBTN) && playerScript->CanUseSP(useSP) == true)
				{
					*isNextAttack = true;
				}
			}

			return false;
		}
		else
		{
			if (nowAnimationTimeRatio < 1.f)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

}

void PlayerState::UpdatePosition(CSSN002PlayerScript * playerScript, Vec3 direction, float speed, float moveStartTimeRatio, float moveEndTimeRatio)
{
	if (playerScript->GetPlayerMovable() == false)
	{
		Vec3 beforePlayerPosition = playerScript->GetBeforePlayerPosition();
		playerScript->Object()->Transform()->SetLocalPos(beforePlayerPosition);
	}
	else
	{
		float curRatioAnimTime = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());
		
		if (moveStartTimeRatio <= curRatioAnimTime && curRatioAnimTime <= moveEndTimeRatio)
		{
			Vec3 walkDirection = direction;
			walkDirection.y = 0.f;

			Vec3 playerPosition = playerScript->Object()->Transform()->GetLocalPos();
			playerPosition += walkDirection * speed;
			playerScript->Object()->Transform()->SetLocalPos(playerPosition);
		}
	}
}

void PlayerState::SetActiveAttackCollision(CSSN002PlayerScript * playerScript, float startActiveTimeRatio, float endActiveTimeRatio)
{
	float curAnimationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());
	if (startActiveTimeRatio <= curAnimationTimeRatio && curAnimationTimeRatio <= endActiveTimeRatio)
	{
		playerScript->GetAttackBoxScript()->SetActiveCollision(true);
	}
}
