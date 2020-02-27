#pragma once
#include <Script.h>
#include "PlayerState.h"

class CSSN002PlayerScript : public CScript
{
private:
	const float PLAYER_MOVE_SPEED;
	const float PLAYER_ROLL_SPEED;

private:
	PlayerState* mPlayerState;

	bool mIsMovable;
	Vec3 mBeforePlayerPosition;

	bool mIsHit;

	int mPlayerHP;
	int mPlayerSP;
	int mPlayerMaxSP;

	bool mIsDead;

	CScript* mAttackBoxScript;

public:
	CSSN002PlayerScript();
	~CSSN002PlayerScript();

public:
	virtual void start();
	virtual void update();

	void SetState(PlayerState* state);
	float GetPlayerMoveSpeed() { return PLAYER_MOVE_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }
	float GetPlayerRollSpeed() { return PLAYER_ROLL_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }

	bool GetPlayerMovable() { return mIsMovable; }

	Vec3 GetBeforePlayerPosition() { return mBeforePlayerPosition; }
	void SetBeforePlayerPosition(Vec3 beforePosition) { mBeforePlayerPosition = beforePosition; }

	void SetHit(bool isHited) 
	{ 
		mIsHit = isHited;

		if (isHited == true)
		{
			mPlayerHP -= 1;
		}
	}

	bool GetHit() { return mIsHit; }

	bool GetDead() { return mIsDead; }

	CScript* GetAttackBoxScript() { return mAttackBoxScript; }

	int GetPlayerHP() { return mPlayerHP; }
	int GetPlayerSP() { return mPlayerSP; }

	void RestoreSP();
	void UseSP(int useSPValue);
	bool CanUseSP(int useSPValue);
};

