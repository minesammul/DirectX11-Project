#include "stdafx.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::Update()
{
	for (UINT i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->Update();
	}
}

void Layer::LateUpdate()
{
	for (UINT i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->LateUpdate();
	}
}

void Layer::FinalUpdate()
{
	for (UINT i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->FinalUpdate();
	}
}

void Layer::Render()
{
	for (UINT i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->Render();
	}
}

void Layer::AddObject(GameObject * _pObj)
{
	m_vecParentObj.push_back(_pObj);
	_pObj->SetLayerIdx(m_uiLayerIdx);
}


