#pragma once
#include "Entity.h"

class Component;
class GameObject : public Entity
{
private:
	Component * m_arrComponent[static_cast<UINT>(COMPONENT_TYPE::END)];

public:
	GameObject();
	virtual ~GameObject();
};

