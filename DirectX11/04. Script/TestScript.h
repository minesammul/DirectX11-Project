#pragma once
#include <Script.h>

class CTestScript : public CScript
{
private:
	float		m_fSpeed;
	float		m_fMul;

public:
	CTestScript();
	~CTestScript();

public:
	virtual void update();
};

