#pragma once
#include <Script.h>

class CSSN020DecalEffectScript : public CScript
{
private:
	CGameObject* mPointLight;

	float mAlphaValue;
	float mLightRange;

public:
	CSSN020DecalEffectScript();
	~CSSN020DecalEffectScript();

public:
	virtual void start();
	virtual void update();

	void OnDecalEffect(Vec3 position);

};

