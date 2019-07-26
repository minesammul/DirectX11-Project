#pragma once
#include "Entity.h"

class Component;
class Transform;
class Camera;
class MeshRender;
class Script;

class GameObject : public Entity
{
private:
	Component * m_arrCom[(UINT)EComponentType::END];
	UINT					m_uiLayerIdx;
	std::vector<Script*>    m_vecScript;

private:
	void SetLayerIdx(UINT _iIdx) { m_uiLayerIdx = _iIdx; }

public:
	template<typename T>
	Script* GetScript();


public:
	GameObject();
	virtual ~GameObject();
	friend class Layer;

public:
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddComponent(Component* _pCom);

	Transform* GetTransform() { return (Transform*)m_arrCom[(UINT)EComponentType::TRANSFORM]; }
	MeshRender* GetMeshRender() { return (MeshRender*)m_arrCom[(UINT)EComponentType::MESHRENDER]; }
	Camera * GetCamera() { return (Camera*)m_arrCom[(UINT)EComponentType::CAMERA]; }



};

template<typename T>
inline Script * GameObject::GetScript()
{
	const type_info& info = typeid(T);

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		if (dynamic_cast<T*>(m_vecScript[i]))
			return m_vecScript[i];
	}

	return nullptr;
}