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

	int playerHP;
	int playerSP;
	int playerMaxSP;

	bool isDead;

	CScript* attackBoxScript;

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

	void SetHit(bool hited) 
	{ 
		isHit = hited;

		if (hited == true)
		{
			playerHP -= 1;
		}
	}

	bool GetHit() { return isHit; }

	bool GetDead() { return isDead; }

	CScript* GetAttackBoxScript() { return attackBoxScript; }

	int GetPlayerHP() { return playerHP; }
	int GetPlayerSP() { return playerSP; }

	void RestoreSP();
	bool UseSP(int useSPValue);
};

