#pragma once
#include "PlayerActionState.h"

class PlayerActionStateSit : public PlayerActionState
{
public:
	PlayerActionStateSit();
	~PlayerActionStateSit();

public:
	// PlayerActionState��(��) ���� ��ӵ�
	virtual void Update(CPlayerScript * player) override;

	static PlayerActionStateSit* GetInstance()
	{
		static PlayerActionStateSit* instance = new PlayerActionStateSit;
		return instance;
	}

};

