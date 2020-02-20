#include "stdafx.h"
#include "SSN004CameraBodyScript.h"


CSSN004CameraBodyScript::CSSN004CameraBodyScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN004CAMERABODYSCRIPT),
	CAMERA_ROTATE_SPEED(100.f)
{
}


CSSN004CameraBodyScript::~CSSN004CameraBodyScript()
{
}

void CSSN004CameraBodyScript::start()
{
	//beforeMousePosition = CKeyMgr::GetInst()->get
}

void CSSN004CameraBodyScript::update()
{
	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->FindGameObject(L"Player", findObject);
	Vec3 vPos = findObject[0]->Transform()->GetLocalPos();
	vPos.y += 250.f;
	Transform()->SetLocalPos(vPos);


	if (CKeyMgr::GetInst()->GetMousePos().x < CKeyMgr::GetInst()->GetPrevMousePos().x)
	{
		Vec3 rotate = Transform()->GetLocalRot();
		rotate.y -= GetRadian(GetCameraRotateSpeed());
		Transform()->SetLocalRot(rotate);
	}
	else if(CKeyMgr::GetInst()->GetMousePos().x > CKeyMgr::GetInst()->GetPrevMousePos().x)
	{
		Vec3 rotate = Transform()->GetLocalRot();
		rotate.y += GetRadian(GetCameraRotateSpeed());
		Transform()->SetLocalRot(rotate);
	}

	if (CKeyMgr::GetInst()->GetMousePos().y > CKeyMgr::GetInst()->GetPrevMousePos().y)
	{
		vector<CGameObject*> findArm;
		CSceneMgr::GetInst()->FindGameObject(L"MainCameraArm", findArm);
		Vec3 bodyToArm = findArm[0]->Transform()->GetWorldPos() - Transform()->GetWorldPos();
		bodyToArm.Normalize();

		float dotValue = Vec3::Down.Dot(bodyToArm);
		float radian = acosf(dotValue);
		float degree = XMConvertToDegrees(radian);

		if (degree > 80.f)
		{
			Vec3 rotate = Transform()->GetLocalRot();
			rotate.x -= GetRadian(GetCameraRotateSpeed());
			Transform()->SetLocalRot(rotate);
		}

	}
	else if (CKeyMgr::GetInst()->GetMousePos().y < CKeyMgr::GetInst()->GetPrevMousePos().y)
	{
		vector<CGameObject*> findArm;
		CSceneMgr::GetInst()->FindGameObject(L"MainCameraArm", findArm);
		Vec3 bodyToArm = findArm[0]->Transform()->GetWorldPos() - Transform()->GetWorldPos();
		bodyToArm.Normalize();

		float dotValue = Vec3::Up.Dot(bodyToArm);
		float radian = acosf(dotValue);
		float degree = XMConvertToDegrees(radian);

		if (degree > 45.f)
		{
			Vec3 rotate = Transform()->GetLocalRot();
			rotate.x += GetRadian(GetCameraRotateSpeed());
			Transform()->SetLocalRot(rotate);
		}

	}

}
