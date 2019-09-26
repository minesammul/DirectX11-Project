#pragma once
#include "Entity.h"

class CResource :
	public CEntity
{
private:
	wstring		m_strPath;	// �����
	int			m_iRefCount;// ���� Ƚ��
	RES_TYPE	m_eType;

public:
	void SetPath(const wstring& _strPath) { m_strPath = _strPath; }
	const wstring& GetPath() { return m_strPath; }
	RES_TYPE GetType() { return m_eType; }

public:
	virtual void Load(const wstring& _strFilePath) {};
	virtual void Save() {};

private:
	void AddRef() { ++m_iRefCount; }
	void SubRef() { --m_iRefCount; }

public:
	CLONE_DISABLE(CResource);

public:
	CResource(RES_TYPE _eType);
	virtual ~CResource();

	template<typename T> friend class CResPtr;
};

