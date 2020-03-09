#include "stdafx.h"
#include "SSN014DirectionLightScript.h"

#include <Light3D.h>
#include "FunctionMgr.h"

CSSN014DirectionLightScript::CSSN014DirectionLightScript():
	CScript((UINT)SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT)
{
}


CSSN014DirectionLightScript::~CSSN014DirectionLightScript()
{
}

void CSSN014DirectionLightScript::DownLightVoluem()
{
	if (mIsLightVoluemDown == true)
	{
		float voluem = CTimeMgr::GetInst()->GetDeltaTime()*mChangeSpeed;
		Vec3 lightVolume = Vec3(voluem, voluem, voluem);

		Vec3 ambientVoluem = Vec3(	Object()->Light3D()->GetLight3DInfo().vAmb.x,
									Object()->Light3D()->GetLight3DInfo().vAmb.y,
									Object()->Light3D()->GetLight3DInfo().vAmb.z);

		Vec3 diffuseVoluem = Vec3(	Object()->Light3D()->GetLight3DInfo().vDiff.x,
									Object()->Light3D()->GetLight3DInfo().vDiff.y,
									Object()->Light3D()->GetLight3DInfo().vDiff.z);

		Vec3 specularVoluem = Vec3(	Object()->Light3D()->GetLight3DInfo().vSpec.x,
									Object()->Light3D()->GetLight3DInfo().vSpec.y,
									Object()->Light3D()->GetLight3DInfo().vSpec.z);

		diffuseVoluem += lightVolume;
		ambientVoluem += lightVolume;
		specularVoluem += lightVolume;

		bool isAmbientDone = false;
		if (ambientVoluem.x >= mGoalAmbient.x)
		{
			ambientVoluem = mGoalAmbient;
			isAmbientDone = true;
		}

		bool isDiffuseDone = false;
		if (diffuseVoluem.x >= mGoalDiffsue.x)
		{
			diffuseVoluem = mGoalDiffsue;
			isDiffuseDone = true;
		}

		bool isSpecularDone = false;
		if (specularVoluem.x >= mGoalSpecular.x)
		{
			diffuseVoluem = mGoalSpecular;
			isSpecularDone = true;
		}

		Object()->Light3D()->SetLightAmbient(ambientVoluem);
		Object()->Light3D()->SetLightDiffuse(diffuseVoluem);
		Object()->Light3D()->SetLightSpecular(specularVoluem);

		if (isDiffuseDone == true && isAmbientDone == true && isSpecularDone == true)
		{
			mIsLightVoluemDown = false;
		}
	}
}

void CSSN014DirectionLightScript::UpdatePosition()
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

void CSSN014DirectionLightScript::start()
{
	mPlayer = CFunctionMgr::GetInst()->FindObject(L"Player");
	mPlayerBeforePosition = mPlayer->Transform()->GetLocalPos();
}

void CSSN014DirectionLightScript::update()
{
	UpdatePosition();
	DownLightVoluem();
}

void CSSN014DirectionLightScript::StartLightVoluemDown(Vec3 startAmbient, Vec3 startDiffuse, Vec3 startSpecular, Vec3 goalAmbient, Vec3 goalDiffuse, Vec3 goalSpecular, float changeSpeed)
{
	mIsLightVoluemDown = true;

	Object()->Light3D()->SetLightAmbient(startAmbient);
	Object()->Light3D()->SetLightDiffuse(startDiffuse);
	Object()->Light3D()->SetLightSpecular(startDiffuse);

	mGoalAmbient = goalAmbient;
	mGoalDiffsue = goalDiffuse;
	mGoalSpecular = goalSpecular;
	mChangeSpeed = changeSpeed;
}
