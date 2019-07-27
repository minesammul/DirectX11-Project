#pragma once
#include "Script.h"

class EnemyScript : public Script
{
public:
	EnemyScript();
	virtual ~EnemyScript();

public:

	void Update() override;

	bool IsCollision();
};

