#pragma once
#include <Script.h>

class CTextureScript : public CScript
{
private:
	CResPtr<CMaterial> cloneMtrl;
	float UValue;
	const float U_VALUE = 0.0001;
	Vec3 beforeMainCameraPosition;

public:
	CTextureScript();
	~CTextureScript();

public:
	virtual void start();
	virtual void update();

};

