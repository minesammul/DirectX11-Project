#pragma once
#include <Script.h>

class CSSN004CameraBodyScript : public CScript
{
private:
	const float CAMERA_ROTATE_SPEED;

public:
	CSSN004CameraBodyScript();
	~CSSN004CameraBodyScript();

private:
	float GetCameraBodyRotateSpeed() { return CAMERA_ROTATE_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }
	void UpdateCameraBodyPosition();
	void OperateCameraBodyRotate();

public:
	virtual void update();
};

