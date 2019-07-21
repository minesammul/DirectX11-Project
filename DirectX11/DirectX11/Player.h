#pragma once
#include "Object.h"
class Player :	public Object
{
private:
	const float m_fSpeed = 200.f;

public:
	Player();
	~Player();

	void Update() override;
	TObject CreateObject() override;
};

