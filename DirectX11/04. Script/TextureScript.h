#pragma once
#include <Script.h>

class CTextureScript : public CScript
{
private:
	const float TEXTURE_U_VALUE = 0.001f;

private:
	CResPtr<CMaterial> cloneMtrl;

	float UValue;
	Vec3 beforeMainCameraPosition;
	CCamera* mainCamera;

public:
	CTextureScript();
	~CTextureScript();

public:
	virtual void start();
	virtual void update();

};

