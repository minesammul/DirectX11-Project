#pragma once
#include <Script.h>
#include "PlayerState.h"

class CSSN002PlayerScript : public CScript
{
private:
	PlayerState* playerState;

public:
	CSSN002PlayerScript();
	~CSSN002PlayerScript();

public:
	virtual void start();
	virtual void update();

	void SetState(PlayerState* state);
};

