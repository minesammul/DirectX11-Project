#pragma once
#include <Engine/Script.h>


class CToolCamScript :
	public CScript
{
public:
	virtual void update();

public:
	CLONE(CToolCamScript)

public:
	CToolCamScript();
	virtual ~CToolCamScript();
};

