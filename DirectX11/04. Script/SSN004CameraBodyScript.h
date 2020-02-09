#pragma once
#include <Script.h>

class CSSN004CameraBodyScript : public CScript
{
private:
	Vec3 beforeMousePosition;

public:
	CSSN004CameraBodyScript();
	~CSSN004CameraBodyScript();

public:
	virtual void start();
	virtual void update();
};

