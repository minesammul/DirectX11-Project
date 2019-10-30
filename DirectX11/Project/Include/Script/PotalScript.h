#pragma once
#include <Script.h>

class CZ4CameraFrameScript;
class CPotalScript : public CScript
{
private:
	CZ4CameraFrameScript* cameraFrameScript;

public:
	CPotalScript();
	~CPotalScript();

public:
	virtual void start();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

