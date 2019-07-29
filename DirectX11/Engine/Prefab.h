#pragma once
#include "GameResource.h"

class GameObject;
class Prefab : public GameResource
{
private:
	GameObject* m_pProto;

public:
	Prefab(GameObject* _pProtoObj);
	virtual ~Prefab();

public:
	GameObject* Instantiate();
};

