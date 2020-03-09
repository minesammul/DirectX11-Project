#include "stdafx.h"
#include "SSN014DirectionLightScript.h"

#include "FunctionMgr.h"

CSSN014DirectionLightScript::CSSN014DirectionLightScript():
	CScript((UINT)SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT)
{
}


CSSN014DirectionLightScript::~CSSN014DirectionLightScript()
{
}

void CSSN014DirectionLightScript::start()
{
	mPlayer = CFunctionMgr::GetInst()->FindObject(L"Player");
	mPlayerBeforePosition = mPlayer->Transform()->GetLocalPos();
}

void CSSN014DirectionLightScript::update()
{
	Vec3 playerNowPosition = mPlayer->Transform()->GetLocalPos();
	if (fabsf(playerNowPosition.x - mPlayerBeforePosition.x) > 1.f)
	{
		float moveValue = playerNowPosition.x - mPlayerBeforePosition.x;
		Vec3 lightPosition = Object()->Transform()->GetLocalPos();
		lightPosition.x += moveValue;
		Object()->Transform()->SetLocalPos(lightPosition);

		mPlayerBeforePosition.x = playerNowPosition.x;
	}

	if (fabsf(playerNowPosition.z - mPlayerBeforePosition.z) > 1.f)
	{
		float moveValue = playerNowPosition.z - mPlayerBeforePosition.z;
		Vec3 lightPosition = Object()->Transform()->GetLocalPos();
		lightPosition.z += moveValue;
		Object()->Transform()->SetLocalPos(lightPosition);

		mPlayerBeforePosition.z = playerNowPosition.z;
	}
}
