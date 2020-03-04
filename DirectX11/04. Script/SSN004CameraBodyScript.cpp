#include "stdafx.h"
#include "SSN004CameraBodyScript.h"

#include "FunctionMgr.h"

CSSN004CameraBodyScript::CSSN004CameraBodyScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN004CAMERABODYSCRIPT),
	CAMERA_ROTATE_SPEED(100.f)
{
}


CSSN004CameraBodyScript::~CSSN004CameraBodyScript()
{
}


void CSSN004CameraBodyScript::UpdateCameraBodyPosition()
{
	Vec3 playerPosition = mPlayerObject->Transform()->GetLocalPos();
	playerPosition.y += 250.f;
	Transform()->SetLocalPos(playerPosition);
}

void CSSN004CameraBodyScript::UpdateCameraBodyRotate()
{
	if (CKeyMgr::GetInst()->GetMousePos().x < CKeyMgr::GetInst()->GetPrevMousePos().x)
	{
		Vec3 rotate = Transform()->GetLocalRot();
		rotate.y -= GetRadian(GetCameraBodyRotateSpeed());
		Transform()->SetLocalRot(rotate);
	}
	else if (CKeyMgr::GetInst()->GetMousePos().x > CKeyMgr::GetInst()->GetPrevMousePos().x)
	{
		Vec3 rotate = Transform()->GetLocalRot();
		rotate.y += GetRadian(GetCameraBodyRotateSpeed());
		Transform()->SetLocalRot(rotate);
	}


	if (CKeyMgr::GetInst()->GetMousePos().y > CKeyMgr::GetInst()->GetPrevMousePos().y)
	{
		Vec3 bodyToArm = mCameraArmObject->Transform()->GetWorldPos() - Transform()->GetWorldPos();
		bodyToArm.Normalize();

		float dotValue = Vec3::Down.Dot(bodyToArm);
		float radian = acosf(dotValue);
		float degree = XMConvertToDegrees(radian);

		if (degree > 80.f)
		{
			Vec3 rotate = Transform()->GetLocalRot();
			rotate.x -= GetRadian(GetCameraBodyRotateSpeed());
			Transform()->SetLocalRot(rotate);
		}

	}
	else if (CKeyMgr::GetInst()->GetMousePos().y < CKeyMgr::GetInst()->GetPrevMousePos().y)
	{
		Vec3 bodyToArm = mCameraArmObject->Transform()->GetWorldPos() - Transform()->GetWorldPos();
		bodyToArm.Normalize();

		float dotValue = Vec3::Up.Dot(bodyToArm);
		float radian = acosf(dotValue);
		float degree = XMConvertToDegrees(radian);

		if (degree > 45.f)
		{
			Vec3 rotate = Transform()->GetLocalRot();
			rotate.x += GetRadian(GetCameraBodyRotateSpeed());
			Transform()->SetLocalRot(rotate);
		}

	}

}

void CSSN004CameraBodyScript::start()
{
	mPlayerObject = CFunctionMgr::GetInst()->FindObject(L"Player");
	mCameraArmObject = CFunctionMgr::GetInst()->FindObject(L"MainCameraArm");
}

void CSSN004CameraBodyScript::update()
{
	UpdateCameraBodyPosition();
	UpdateCameraBodyRotate();
}
