#include "stdafx.h"
#include "Prefab.h"

#include "GameObject.h"

Prefab::Prefab(GameObject* _pProtoObj):
	m_pProto(_pProtoObj)
{
	assert(m_pProto);
}


Prefab::~Prefab()
{
	delete m_pProto;
}

GameObject * Prefab::Instantiate()
{
	return m_pProto->Clone();
}
