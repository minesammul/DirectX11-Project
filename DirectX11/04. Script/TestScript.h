#pragma once
#include <Script.h>

class CTestScript : public CScript
{
private:
	float		m_fSpeed;
	float		m_fMul;

	Vec3 mPlayerBeforePosition;
	CGameObject* mPlayer;
public:
	CTestScript();
	~CTestScript();

private:
	void ControlCamera();

public:
	virtual void start();
	virtual void update();
};

