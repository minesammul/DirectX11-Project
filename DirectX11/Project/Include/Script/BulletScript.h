#pragma once
#include <Script.h>

class CBulletScript :
	public CScript
{
private:
	float		m_fSpeed;
	
public:
	virtual void update();

public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }	
	CLONE(CBulletScript);

public:
	CBulletScript();
	virtual ~CBulletScript();
};

