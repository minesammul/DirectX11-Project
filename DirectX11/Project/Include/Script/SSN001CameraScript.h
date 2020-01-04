#pragma once
#include <Script.h>

class CSSN001CameraScript : public CScript
{
public:
	CSSN001CameraScript();
	~CSSN001CameraScript();

private:
	float		m_fSpeed;
	float		m_fMul;

public:
	virtual void update();
};

