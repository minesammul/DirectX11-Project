#pragma once
#include <Script.h>

class CSSN012SkyBoxScript : public CScript
{
private:
	Vec2 mUV;

public:
	CSSN012SkyBoxScript();
	~CSSN012SkyBoxScript();

public:
	virtual void start();
	virtual void update();
};

