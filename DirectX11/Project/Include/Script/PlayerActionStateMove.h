#pragma once
#include "PlayerActionState.h"

class PlayerActionStateMove : public PlayerActionState
{
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

