#pragma once
#include "Entity.h"

class GameResource : public Entity
{
public:
	GameResource();
	virtual ~GameResource();

	CLONE_DISABLE(GameResource);
};

