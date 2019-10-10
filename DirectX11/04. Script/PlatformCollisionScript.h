#pragma once
#include <Script.h>

class CPlatformCollisionScript : public CScript
{
public:
	CPlatformCollisionScript();
	~CPlatformCollisionScript();

public:
	CLONE(CPlatformCollisionScript);

public:
	virtual void update();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

