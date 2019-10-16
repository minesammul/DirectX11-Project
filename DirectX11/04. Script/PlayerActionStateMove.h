#pragma once
#include "PlayerActionState.h"

class CPlatformRightCollisionScript;
class PlayerActionStateMove : public PlayerActionState
{
private:
	CPlatformRightCollisionScript* platformRightCollisionScript;

public:
	PlayerActionStateMove();
	~PlayerActionStateMove();

private:
	void FindAnimation(CPlayerScript * player);
	void ActionState(CPlayerScript * player);
	void TransactionState(CPlayerScript * player);

public:
	virtual void Update(CPlayerScript * player) override;
	static PlayerActionStateMove* GetInstance()
	{
		static PlayerActionStateMove* instance = new PlayerActionStateMove;
		return instance;
	}

};

