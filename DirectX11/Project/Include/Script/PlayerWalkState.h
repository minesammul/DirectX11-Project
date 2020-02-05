#pragma once
#include "PlayerState.h"

enum class WALK_TYPE
{
	FRONT=0,
	BACK,
	LEFT,
	RIGHT,
	END
};

class PlayerWalkState : public PlayerState
{
private:
	int findAnimationIndex[(int)WALK_TYPE::END];

public:
	PlayerWalkState();
	~PlayerWalkState();

public:
	// PlayerState��(��) ���� ��ӵ�
	static PlayerWalkState* GetInstance();

	virtual void Init(CSSN002PlayerScript * playerScript) override;
	virtual void Update(CSSN002PlayerScript * playerScript) override;
	virtual void Exit(CSSN002PlayerScript * playerScript) override;


};

