#pragma once
#include <Script.h>

class CPotalScript : public CScript
{
public:
	CPotalScript();
	~CPotalScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

