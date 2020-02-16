#pragma once
#include <Script.h>
#include "PlayerState.h"

class CSSN002PlayerScript : public CScript
{
private:
	const float PLAYER_MOVE_SPEED;

private:
	PlayerState* playerState;

	bool isMovable;
	Vec3 beforePlayerPosition;

	bool isHit;

public:
	CSSN002PlayerScript();
	~CSSN002PlayerScript();

public:
	virtual void start();
	virtual void update();

	void SetState(PlayerState* state);
	float GetPlayerMoveSpeed() { return PLAYER_MOVE_SPEED; }
	float GetPlayerRollSpeed() { return PLAYER_MOVE_SPEED * 3.f; }

	bool GetPlayerMovable() { return isMovable; }

	Vec3 GetBeforePlayerPosition() { return beforePlayerPosition; }
	void SetBeforePlayerPosition(Vec3 beforePosition) { beforePlayerPosition = beforePosition; }

	void SetHit(bool hited) { isHit = hited; }
	bool GetHit() { return isHit; }
};

