#pragma once
#include <Script.h>

class CMonsterScript :
	public CScript
{

public:
	virtual void update();


public:
	CLONE(CMonsterScript);

public:
	CMonsterScript();
	virtual ~CMonsterScript();
};

