#include "stdafx.h"
#include "Prefab.h"

#include "GameObject.h"

CPrefab::CPrefab() : 
	m_pProto(nullptr)
{
}

CPrefab::CPrefab(CGameObject * _pProtoObj)
	: m_pProto(_pProtoObj)
{
}

CPrefab::~CPrefab()
{
	SAFE_DELETE(m_pProto);
}

CGameObject * CPrefab::Instantiate()
{	
	return m_pProto->Clone();
}