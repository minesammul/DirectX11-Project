#include "stdafx.h"
#include "Scene.h"

#include "Layer.h"

Scene::Scene()
	: m_arrLayer{}
{
}


Scene::~Scene()
{
}

void Scene::Awake()
{
}

void Scene::Start()
{
}

void Scene::Update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == m_arrLayer[i])
			continue;

		m_arrLayer[i]->Update();
	}
}

void Scene::LateUpdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == m_arrLayer[i])
			continue;

		m_arrLayer[i]->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == m_arrLayer[i])
			continue;

		m_arrLayer[i]->FinalUpdate();
	}
}


void Scene::Render()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == m_arrLayer[i])
			continue;
		
		m_arrLayer[i]->Render();
	}
}

void Scene::AddLayer(const std::wstring & _strLayerName, UINT _iLayerIdx)
{
	if (nullptr != m_arrLayer[_iLayerIdx])
		return;

	m_arrLayer[_iLayerIdx] = new Layer;
	m_arrLayer[_iLayerIdx]->SetName(_strLayerName);

}

void Scene::AddLayer(Layer * _pLayer, UINT _iLayerIdx)
{
	assert(!m_arrLayer[_iLayerIdx]);

	m_arrLayer[_iLayerIdx] = _pLayer;

}

void Scene::AddObject(const std::wstring & _strLayerName, GameObject * _pObj)
{
	Layer* pFindLayer = FindLayer(_strLayerName);
	assert(pFindLayer);
	pFindLayer->AddObject(_pObj);

}

void Scene::AddObject(UINT _iLayerIdx, GameObject * _pObj)
{
	assert(m_arrLayer[_iLayerIdx]);
	m_arrLayer[_iLayerIdx]->AddObject(_pObj);
}

Layer * Scene::FindLayer(const std::wstring & _strLayer)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == m_arrLayer[i])
			continue;

		if (m_arrLayer[i]->GetName() == _strLayer)
		{
			return m_arrLayer[i];
		}
	}

	return nullptr;
}
