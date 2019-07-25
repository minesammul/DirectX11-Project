#pragma once
#include "Entity.h"

class Layer;
class GameObject;

class Scene : public Entity
{
private:
	Layer * m_arrLayer[MAX_LAYER];


public:
	Scene();
	~Scene();

public:
	void Awake();
	void Start();

	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddLayer(const std::wstring& _strLayerName, UINT _iLayerIdx);
	void AddLayer(Layer* _pLayer, UINT _iLayerIdx);

	void AddObject(const std::wstring& _strLayerName, GameObject* _pObj);
	void AddObject(UINT _iLayerIdx, GameObject* _pObj);

	Layer* FindLayer(const std::wstring& _strLayer);

};

