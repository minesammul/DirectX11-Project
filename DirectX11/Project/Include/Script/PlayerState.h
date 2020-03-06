#pragma once
#include <Animator3D.h>
#include "FunctionMgr.h"

class CSSN002PlayerScript;
class PlayerState
{
private:
	int mUseSPAmount;

public:
	PlayerState();
	~PlayerState();

protected:
	bool CheckDieState(CSSN002PlayerScript* playerScript);
	bool CheckHitedState(CSSN002PlayerScript* playerScript);

	virtual bool CheckIdleState(CSSN002PlayerScript* playerScript);

	bool CheckWalkFrontState(CSSN002PlayerScript* playerScript);
	bool CheckWalkBackState(CSSN002PlayerScript* playerScript);
	bool CheckWalkLeftState(CSSN002PlayerScript* playerScript);
	bool CheckWalkRightState(CSSN002PlayerScript* playerScript);

	bool CheckRollState(CSSN002PlayerScript * playerScript, int useSP);

	bool CheckHealState(CSSN002PlayerScript* playerScript);

	bool CheckAttackState(CSSN002PlayerScript* playerScript, int useSP, float nextAttackStartTimeRatio, float nextAttackEndTimeRatio, bool* isNextAttack);

	void UpdatePosition(CSSN002PlayerScript * playerScript, Vec3 direction, float speed, float moveStartTimeRatio, float moveEndTimeRatio);

	void SetActiveAttackCollision(CSSN002PlayerScript * playerScript, float startActiveTimeRatio, float endActiveTimeRatio);

public:
	virtual void Init(CSSN002PlayerScript* playerScript) = 0;
	virtual void Update(CSSN002PlayerScript* playerScript) = 0;

	int GetUseSPAmount() { return mUseSPAmount; }
	void SetUseSPAmount(int useSPAmount) { mUseSPAmount = useSPAmount; }
};

