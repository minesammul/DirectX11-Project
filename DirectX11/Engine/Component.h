#pragma once
#include "Entity.h"

#include "GameObject.h"

class Component : public Entity
{
private:
	EComponentType	m_eComponentType;
	GameObject*		m_pObject;


public:
	Component();
	CLONE(Component);
	Component(const Component& _com);

	virtual ~Component();

	friend class GameObject;

protected:
	void SetComponentType(EComponentType _eType) { m_eComponentType = _eType; }
	Transform* GetTransform() { return m_pObject->GetTransform(); }
	MeshRender* GetMeshrender() { return m_pObject->GetMeshRender(); }
private:
	void SetGameObject(GameObject* _pObject) { m_pObject = _pObject; }
public:
	GameObject * Object() { return m_pObject; }

public:
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void FinalUpdate() {};

public:
	EComponentType GetCompnentType() { return m_eComponentType; }

};

