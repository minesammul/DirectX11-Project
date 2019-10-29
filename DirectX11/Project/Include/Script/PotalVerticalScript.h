#pragma once
#include <Script.h>

class CPotalVerticalScript : public CScript
{
public:
	CPotalVerticalScript();
	~CPotalVerticalScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

