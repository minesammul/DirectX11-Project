#pragma once
#include <Script.h>

class CEffectScript : public CScript
{
private:
	CResPtr<CPrefab>	monsterPrefab;

public:
	CEffectScript();
	~CEffectScript();

public:
	virtual void start();
	virtual void update();
};

