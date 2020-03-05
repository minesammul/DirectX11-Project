#include "stdafx.h"
#include "PlayerState.h"
#include "SSN002PlayerScript.h"


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

bool PlayerState::CheckAttack1State(CSSN002PlayerScript * playerScript, int useSP)
{
	return (KEYTAB(KEY_TYPE::KEY_LBTN) && playerScript->CanUseSP(useSP) == true);
}

bool PlayerState::CheckAttack2State(CSSN002PlayerScript * playerScript, int useSP, bool& isNextAttack)
{
	float animationTimeRatio = CFunctionMgr::GetInst()->GetNowAnimationTimeRatio(playerScript->Object());

	if (isNextAttack == false)
	{
		if (animationTimeRatio >= 0.5f)
		{
			if (KEYTAB(KEY_TYPE::KEY_LBTN) && playerScript->CanUseSP(useSP) == true)
			{
				isNextAttack = true;
			}
		}

		return false;
	}
	else
	{
		if (animationTimeRatio < 1.f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
