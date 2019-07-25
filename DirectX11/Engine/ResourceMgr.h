#pragma once
#include "GameResource.h"

#include "Mesh.h"
#include "Sound.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

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

	iter = m_mapRes[(UINT)eType].find(_strKey);
	if (iter == m_mapRes[(UINT)eType].end())
		return nullptr;
	else
		return (T*)iter->second;
}