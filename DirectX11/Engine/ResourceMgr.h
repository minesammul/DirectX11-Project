#pragma once
#include "GameResource.h"

#include "Mesh.h"
#include "Sound.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Prefab.h"

class ResourceMgr
{
private:
	std::map<std::wstring, GameResource*> m_mapRes[(UINT)EResourceType::END];

public:
	ResourceMgr();
	~ResourceMgr();

public:
	static ResourceMgr* GetInstance()
	{
		static ResourceMgr instance;
		return &instance;
	}

public:
	void Init();

private:
	void CreateDefaultMesh();
	void CreateDefaultShader();

public:
	template<typename T>
	T* FindRes(const std::wstring& _strKey);

	template<typename T>
	void AddRes(const std::wstring& _strKey, GameResource* _pResource);
};

template<typename T>
inline T* ResourceMgr::FindRes(const std::wstring & _strKey)
{
	std::map<std::wstring, GameResource*>::iterator iter;

	EResourceType eType = EResourceType::END;

	if (typeid(T).hash_code() == typeid(Mesh).hash_code())
		eType = EResourceType::MESH;
	else if (typeid(T).hash_code() == typeid(Texture).hash_code())
		eType = EResourceType::TEXTURE;
	else if (typeid(T).hash_code() == typeid(Shader).hash_code())
		eType = EResourceType::SHADER;
	else if (typeid(T).hash_code() == typeid(Sound).hash_code())
		eType = EResourceType::SOUND;
	else if (typeid(T).hash_code() == typeid(Material).hash_code())
		eType = EResourceType::MATERIAL;
	else if (typeid(T).hash_code() == typeid(Prefab).hash_code())
		eType = EResourceType::PREFAB;

	iter = m_mapRes[(UINT)eType].find(_strKey);
	if (iter == m_mapRes[(UINT)eType].end())
		return nullptr;
	else
		return (T*)iter->second;
}

template<typename T>
inline void ResourceMgr::AddRes(const std::wstring & _strKey, GameResource * _pResource)
{
	std::map<std::wstring, GameResource*>::iterator iter;

	EResourceType eType = EResourceType::END;

	if (typeid(T).hash_code() == typeid(Mesh).hash_code())
		eType = EResourceType::MESH;
	else if (typeid(T).hash_code() == typeid(Texture).hash_code())
		eType = EResourceType::TEXTURE;
	else if (typeid(T).hash_code() == typeid(Shader).hash_code())
		eType = EResourceType::SHADER;
	else if (typeid(T).hash_code() == typeid(Sound).hash_code())
		eType = EResourceType::SOUND;
	else if (typeid(T).hash_code() == typeid(Material).hash_code())
		eType = EResourceType::MATERIAL;
	else if (typeid(T).hash_code() == typeid(Prefab).hash_code())
		eType = EResourceType::PREFAB;

	iter = m_mapRes[(UINT)eType].find(_strKey);
	assert(iter == m_mapRes[(UINT)eType].end());

	m_mapRes[(UINT)eType].insert(make_pair(_strKey, _pResource));
	_pResource->SetName(_strKey);
}