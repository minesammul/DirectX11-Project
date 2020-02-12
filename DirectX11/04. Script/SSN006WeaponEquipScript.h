#pragma once
#include <Script.h>

class CSSN006WeaponEquipScript : public CScript
{
private:
	int findEquipMeshIndex;
	Vec3 initialPosition;
	Vec3 initialRotate;

public:
	CSSN006WeaponEquipScript();
	~CSSN006WeaponEquipScript();

public:
	virtual void start();
	virtual void update();
};

