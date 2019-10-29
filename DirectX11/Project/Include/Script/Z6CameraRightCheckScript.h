#pragma once
#include <Script.h>

class CZ6CameraRightCheckScript : public CScript
{
private:
	bool isCollision;

public:
	CZ6CameraRightCheckScript();
	~CZ6CameraRightCheckScript();

public:
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	bool GetIsCollision(void)
	{
		return isCollision;
	}

};

