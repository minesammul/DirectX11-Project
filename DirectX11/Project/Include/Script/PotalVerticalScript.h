#pragma once
#include <Script.h>

class CZ4CameraFrameScript;
class CPotalVerticalScript : public CScript
{
private:
	CZ4CameraFrameScript* cameraFrameScript;

public:
	CPotalVerticalScript();
	~CPotalVerticalScript();

public:
	virtual void start();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

