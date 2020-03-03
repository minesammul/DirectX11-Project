#pragma once
#include <Script.h>

class CSSN004CameraBodyScript : public CScript
{
private:
	const float CAMERA_ROTATE_SPEED;

private:
	CGameObject* mPlayerObject;
	CGameObject* mCameraArmObject;

public:
	CSSN004CameraBodyScript();
	~CSSN004CameraBodyScript();

private:
	float GetCameraBodyRotateSpeed() { return CAMERA_ROTATE_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }
	void UpdateCameraBodyPosition();
	void OperateCameraBodyRotate();

public:
	virtual void start();
	virtual void update();
};

