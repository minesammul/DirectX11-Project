#pragma once
#include "Entity.h"

class CResource :
	public CEntity
{
private:
	wstring		m_strPath;	// �����
	int			m_iRefCount;// ���� Ƚ��

public:
	void SetPath(const wstring& _strPath) { m_strPath = _strPath; }
	const wstring& GetPath() { return m_strPath; }

public:
	virtual void Load(const wstring& _strFilePath) {};
	virtual void Save() {};

private:
	void AddRef() { ++m_iRefCount; }
	void SubRef() { --m_iRefCount; }

public:
	CLONE_DISABLE(CResource);

public:
	CResource();
	virtual ~CResource();

	template<typename T> friend class CResPtr;
};

