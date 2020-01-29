#pragma once
#include <Script.h>

class CTestScript : public CScript
{
private:
	int aniIndex;

public:
	CTestScript();
	~CTestScript();

public:
	virtual void update();
};

