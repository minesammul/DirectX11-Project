#pragma once
#include <Script.h>

class CSSN001CameraScript : public CScript
{
private:
	const float UP_AXIX_ERROR_RANGE_VALUE;

private:
	CGameObject* mMainCameraArm;
	CGameObject* mMainCameraBody;

public:
	CSSN001CameraScript();
	~CSSN001CameraScript();

private:
	void FindObject(CGameObject** findResultObject, wstring findObjectName);
	void UpdatePosition();
	void UpdateLookAt();

public:
	virtual void start();
	virtual void update();
};

