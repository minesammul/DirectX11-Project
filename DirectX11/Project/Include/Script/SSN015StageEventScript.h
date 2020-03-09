#pragma once
#include <Script.h>

class CSSN015StageEventScript : public CScript
{
public:
	CSSN015StageEventScript();
	~CSSN015StageEventScript();

public:
	virtual void OnCollisionEnter(CCollider3D* _pOther);
};

