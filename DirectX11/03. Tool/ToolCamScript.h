#pragma once
#include <Engine/Script.h>


class CToolCamScript :
	public CScript
{
private:
	float		m_fSpeed;
	float		m_fMul;

public:
	virtual void update();

public:
	CLONE(CToolCamScript)

public:
	CToolCamScript();
	virtual ~CToolCamScript();
};

