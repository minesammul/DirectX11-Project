#pragma once
#include <Script.h>
#include "MonsterState.h"

class CSSN008AttackBoxScript;
class CSSN007MonsterScript : public CScript
{
private:
	const float MONSTER_MOVE_SPEED;
	const float MONSTER_ROTATE_SPEED;

private:
	MonsterState* mMonsterState;

	CGameObject* mPlayerObject;

	CSSN008AttackBoxScript* mAttackBoxScript;

	bool mIsHit;

	int mMonsterHP;

	bool mIsDead;

public:
	CSSN007MonsterScript();
	~CSSN007MonsterScript();

private:
	void CheckHited();
	void CheckDie();


public:
	virtual void start();
	virtual void update();

	void SetState(MonsterState* state);
	CGameObject* GetPlayerObject();
	CSSN008AttackBoxScript* GetAttackBoxScript();

	void SetHit(bool isHit) 
	{
		mIsHit = isHit;

		if (isHit == true)
		{
			mMonsterHP -= 1;
		}
	}

	bool GetHit() { return mIsHit; }

	bool GetDead() { return mIsDead; }

	int GetMonsterHP() { return mMonsterHP; }

	float GetMonsterMoveSpeed() { return MONSTER_MOVE_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }
	float GetMonsterRotateSpeed() { return MONSTER_ROTATE_SPEED * CTimeMgr::GetInst()->GetDeltaTime(); }
};

