#pragma once
#include <Script.h>

class CSSN006WeaponEquipScript : public CScript
{
private:
	int mFindEquipMeshIndex;
	Vec3 mInitialPosition;
	Vec3 mInitialRotate;

public:
	CSSN006WeaponEquipScript();
	~CSSN006WeaponEquipScript();

public:
	virtual void start();
	virtual void update();
};

