#pragma once
#include "Entity.h"

class GameObject;

class Layer : public Entity
{
private:
	std::vector<GameObject*>	m_vecParentObj;

public:
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddObject(GameObject* _pObj);


public:
	Layer();
	virtual ~Layer();
};

