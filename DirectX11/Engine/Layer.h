#pragma once
#include "Entity.h"

class GameObject;

class Layer : public Entity
{
private:
	std::vector<GameObject*>	m_vecParentObj;
	UINT						m_uiLayerIdx;    // Scene ���� ���° layer ���� 

public:
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddObject(GameObject* _pObj);

	UINT GetLayerIdx() { return m_uiLayerIdx; }

private:
	void SetLayerIdx(UINT _iIdx) { m_uiLayerIdx = _iIdx; }

public:
	Layer();
	virtual ~Layer();
	friend class Scene;
};

