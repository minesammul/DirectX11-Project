#pragma once
#include <Script.h>

class CZ5CameraTopCheckScript : public CScript
{
private:
	bool isCollision;

public:
	CZ5CameraTopCheckScript();
	~CZ5CameraTopCheckScript();

public:
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	bool GetIsCollision(void)
	{
		return isCollision;
	}
};

