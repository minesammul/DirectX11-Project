#pragma once
#include "Resource.h"

class CGameObject;

class CPrefab :
	public CResource
{
private:
	CGameObject*	m_pProto;

public:
	CPrefab(CGameObject* _pProtoObj);
	virtual ~CPrefab();
};

