#pragma once
#include <Script.h>

class CSSN014DirectionLightScript : public CScript
{
private:
	bool mIsLightVoluemDown;
	bool mIsLightVoluemUp;

	Vec3 mGoalAmbient;
	Vec3 mGoalDiffsue;
	Vec3 mGoalSpecular;
	float mChangeSpeed;

public:
	CSSN014DirectionLightScript();
	~CSSN014DirectionLightScript();

private:
	void DownLightVoluem();
	void UpLightVoluem();

public:
	virtual void start();
	virtual void update();

	void StartLightVoluemDown(Vec3 startAmbient, Vec3 startDiffuse, Vec3 startSpecular, Vec3 goalAmbient, Vec3 goalDiffuse, Vec3 goalSpecular, float changeSpeed);
	void StartLightVoluemUp(Vec3 startAmbient, Vec3 startDiffuse, Vec3 startSpecular, Vec3 goalAmbient, Vec3 goalDiffuse, Vec3 goalSpecular, float changeSpeed);
	
	Vec3 GetPosition();
	void SetPosition(Vec3 position);
};

