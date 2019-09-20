#include "stdafx.h"
#include "Prefab.h"

#include "GameObject.h"

CPrefab::CPrefab(CGameObject * _pProtoObj)
	: m_pProto(_pProtoObj)
{
	assert(m_pProto);
}

CPrefab::~CPrefab()
{
	SAFE_DELETE(m_pProto);
}

CGameObject * CPrefab::Instantiate()
{	
	return m_pProto->Clone();
}