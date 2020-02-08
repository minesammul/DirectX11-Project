#pragma once
#include <Script.h>
#include "PlayerState.h"

class CSSN002PlayerScript : public CScript
{
private:
	PlayerState* playerState;

	const float PLAYER_MOVE_SPEED;

public:
	CSSN002PlayerScript();
	~CSSN002PlayerScript();

public:
	virtual void start();
	virtual void update();

	void SetState(PlayerState* state);
	float GetPlayerMoveSpeed() { return PLAYER_MOVE_SPEED; }
	float GetPlayerRollSpeed() { return PLAYER_MOVE_SPEED * 3.f; }
};

