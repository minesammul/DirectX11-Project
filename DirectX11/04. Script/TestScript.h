#pragma once
#include <Script.h>

class CTestScript : public CScript
{
private:
	float		m_fSpeed;
	float		m_fMul;

	CGameObject* mainCamera;
	float effectValue;
	bool isUp;
public:
	CTestScript();
	~CTestScript();

private:
	void ControlCamera();

public:
	virtual void start();
	virtual void update();
};

