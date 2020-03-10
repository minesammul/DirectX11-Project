#pragma once
#include <Script.h>

enum class EFFECT_KIND
{
	THUNDER_EFFECT,
	END
};

enum class EFFECT_OPERATER_KIND
{
	UP,
	DOWN,
	END
};

class CSSN018EffectScript : public CScript
{
private:
	float mEffectValue;
	bool mIsUp;
	bool mIsDown;
	float mValueSpeed;

public:
	CSSN018EffectScript();
	~CSSN018EffectScript();

private:
	void UpEffectValue();
	void DownEffectValue();

public:
	virtual void start();
	virtual void update();

	void OperaterEffect(EFFECT_KIND effectKind, EFFECT_OPERATER_KIND effectOperaterKind, float valueSpeed);
};

