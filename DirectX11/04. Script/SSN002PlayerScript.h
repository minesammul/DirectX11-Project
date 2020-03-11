#pragma once
#include <Script.h>
#include "PlayerState.h"

class CSSN008AttackBoxScript;

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
	int mPlayerMaxHP;
	int mPlayerSP;
	int mPlayerMaxSP;

	int mPlayerHealCount;
	int mPlayerMaxHealCount;

	bool mIsDead;

	CSSN008AttackBoxScript* mAttackBoxScript;

public:
	CSSN002PlayerScript();
	~CSSN002PlayerScript();

private:
	void CheckDie();
	void LookAtFront();
	void CheckMovable();

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

	CSSN008AttackBoxScript* GetAttackBoxScript() { return mAttackBoxScript; }

	int GetPlayerHP() { return mPlayerHP; }
	int GetPlayerMaxHP() { return mPlayerMaxHP; }
	int GetPlayerSP() { return mPlayerSP; }
	int GetPlayerMaxSP() { return mPlayerMaxSP; }
	int GetPlayerHealCount() { return mPlayerHealCount; }
	int GetPlayerMaxHealCount() { return mPlayerMaxHealCount; }

	bool UseHeal(int healValue);

	void RestoreSP();
	void UseSP(int useSPValue);
	bool CanUseSP(int useSPValue);
};

