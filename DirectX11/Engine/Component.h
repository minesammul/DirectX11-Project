#pragma once
#include "Entity.h"
class Component :	public Entity
{
private:
	COMPONENT_TYPE m_eComponentType;

public:
	Component();
	virtual ~Component();

public:
	void SetComponentType(COMPONENT_TYPE eComponentType)
	{
		m_eComponentType = eComponentType;
	}

	COMPONENT_TYPE GetComponentType()
	{
		return m_eComponentType;
	}
};

