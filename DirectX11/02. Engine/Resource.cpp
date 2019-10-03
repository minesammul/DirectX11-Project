#include "stdafx.h"
#include "Resource.h"


void CResource::SaveToScene(FILE * _pFile)
{
	// Ű��
	SaveWString(GetName().c_str(), _pFile);

	// ���
	SaveWString(m_strPath.c_str(), _pFile);
}

bool CResource::LoadFromScene(FILE * _pFile)
{
	// Ű��
	SetName(LoadWString(_pFile));

	// ���
	m_strPath = LoadWString(_pFile);
	return false;
}

CResource::CResource(RES_TYPE _eType) :
	m_eType(_eType)
{
}


CResource::~CResource()
{
}