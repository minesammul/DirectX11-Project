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

	//bool CheckAttack1State(CSSN002PlayerScript* playerScript, int useSP);
	//bool CheckAttack2State(CSSN002PlayerScript* playerScript, int useSP, bool& isNextAttack);
	bool CheckAttackState(CSSN002PlayerScript* playerScript, int useSP, float attackStartTimeRatio, float attackEndTimeRatio, bool* isNextAttack);

public:
	virtual void Init(CSSN002PlayerScript* playerScript) = 0;
	virtual void Update(CSSN002PlayerScript* playerScript) = 0;

	int GetUseSPAmount() { return mUseSPAmount; }
	void SetUseSPAmount(int useSPAmount) { mUseSPAmount = useSPAmount; }
};

