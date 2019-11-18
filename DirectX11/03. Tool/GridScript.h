#pragma once
#include <Engine/Script.h>

class CGridScript :
	public CScript
{
private:
	

public:
	virtual void update();	

public:
	CLONE(CGridScript);

public:
	CGridScript();
	virtual ~CGridScript();
};

