#pragma once
#include <Animator3D.h>
class CSSN002PlayerScript;

class PlayerState
{
public:
	PlayerState();
	~PlayerState();

public:
	virtual void Init(CSSN002PlayerScript* playerScript) = 0;
	virtual void Update(CSSN002PlayerScript* playerScript) = 0;
	virtual void Exit(CSSN002PlayerScript* playerScript) = 0;
};
