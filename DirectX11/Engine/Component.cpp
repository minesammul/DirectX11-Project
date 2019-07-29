#include "stdafx.h"
#include "Component.h"


Component::Component()
{
}

Component::Component(const Component & _com) :
	Entity(_com)
{
	m_eComponentType = _com.m_eComponentType;
	m_pObject = nullptr;
}


Component::~Component()
{
}
