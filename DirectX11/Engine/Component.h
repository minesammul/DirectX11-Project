#pragma once
#include "Entity.h"

class GameObject;
class Component : public Entity
{
private:
	EComponentType	m_eComponentType;
	GameObject*		m_pObject;


public:
	Component();
	virtual ~Component();
	
	friend class GameObject;

protected:
	void SetComponentType(EComponentType _eType) { m_eComponentType = _eType; }
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

