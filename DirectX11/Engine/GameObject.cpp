#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Script.h"

GameObject::GameObject()
	: m_arrCom{}
{
}


GameObject::GameObject(const GameObject & _origin):
	Entity(_origin)
{
	for (UINT i = 0; i < (UINT)EComponentType::END; ++i)
	{
		m_arrCom[i] = _origin.m_arrCom[i]->Clone();
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript.push_back(_origin.m_vecScript[i]->Clone());
	}
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	for (UINT i = 0; i < (UINT)EComponentType::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->Update();
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Update();
	}
}

void GameObject::LateUpdate()
{
	for (UINT i = 0; i < (UINT)EComponentType::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->LateUpdate();
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)EComponentType::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalUpdate();
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->FinalUpdate();
	}
}

void GameObject::Render()
{
	if (!GetMeshRender())
	{
		return;
	}

	((MeshRender*)m_arrCom[(UINT)EComponentType::MESHRENDER])->Render();

}

void GameObject::AddComponent(Component * _pCom)
{
	// GameObject 가 해당 컴포넌트를 이미 가지고 있는 경우
	EComponentType eType = _pCom->GetCompnentType();

	if (EComponentType::SCRIPT == eType)
	{
		m_vecScript.push_back((Script*)_pCom);
	}
	else
	{
		assert(!m_arrCom[(UINT)eType]);
		m_arrCom[(UINT)eType] = _pCom;
	}	_pCom->SetGameObject(this);

}


