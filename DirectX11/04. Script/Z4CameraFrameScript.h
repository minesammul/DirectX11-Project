#pragma once
#include <Script.h>

class CZ3CameraBottomCheckScript;
class CZ5CameraTopCheckScript;
class CZ6CameraRightCheckScript;
class CZ7CameraLeftCheckScript;

class CZ4CameraFrameScript : public CScript
{
private:
	CGameObject* target;

	//CGameObject* cameraBottomCheck;
	CZ3CameraBottomCheckScript* cameraBottomScript;
	CZ5CameraTopCheckScript* cameraTopScript;
	CZ6CameraRightCheckScript* cameraRightScript;
	CZ7CameraLeftCheckScript* cameraLeftScript;

	Vec3 beforeTargetPosition;

public:
	CZ4CameraFrameScript();
	~CZ4CameraFrameScript();

public:
	virtual void start();
	virtual void update();
};

