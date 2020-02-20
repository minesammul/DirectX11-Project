#pragma once
#include <Script.h>

class CSSN004CameraBodyScript : public CScript
{
private:
	const float CAMERA_ROTATE_SPEED;

private:
	Vec3 beforeMousePosition;

public:
	CSSN004CameraBodyScript();
	~CSSN004CameraBodyScript();

private:
	float GetCameraRotateSpeed() { return CAMERA_ROTATE_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }

public:
	virtual void start();
	virtual void update();
};

