#include "stdafx.h"
#include "SSN001CameraScript.h"

#include "FunctionMgr.h"

CSSN001CameraScript::CSSN001CameraScript():
	CScript((UINT)SCRIPT_TYPE::SSN001CAMERASCRIPT),
	UP_AXIX_ERROR_RANGE_VALUE(0.1f)
{
}


CSSN001CameraScript::~CSSN001CameraScript()
{
}


void CSSN001CameraScript::UpdatePosition()
{
	Vec3 mainCameraArmWorldPosition = mMainCameraArm->Transform()->GetWorldPos();
	Transform()->SetLocalPos(mainCameraArmWorldPosition);
}

void CSSN001CameraScript::UpdateLookAt()
{
	Vec3 mainCameraBodyPosition = mMainCameraBody->Transform()->GetWorldPos();
	Vec3 mainCameraArmWorldPosition = mMainCameraArm->Transform()->GetWorldPos();
	Vec3 cameraLookDirection = mainCameraBodyPosition - mainCameraArmWorldPosition;

	if (-UP_AXIX_ERROR_RANGE_VALUE <= cameraLookDirection.z && cameraLookDirection.z <= UP_AXIX_ERROR_RANGE_VALUE)
	{
		cameraLookDirection.z = 1.f;
	}

	Transform()->SetLookAt(cameraLookDirection);
}

void CSSN001CameraScript::start()
{
	mMainCameraArm = CFunctionMgr::GetInst()->FindObject(L"MainCameraArm");
	mMainCameraBody = CFunctionMgr::GetInst()->FindObject(L"MainCameraBody");
}

void CSSN001CameraScript::update()
{
	UpdatePosition();
	UpdateLookAt();
}
