#pragma once
#include "Script.h"

class PlayerScript : public Script
{
public:
	PlayerScript();
	virtual ~PlayerScript();

public:
	virtual void Update();

private:
	void CreateBullet();
};

