#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"

GameObject::GameObject()
	: m_arrCom{}
{
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
}

void GameObject::LateUpdate()
{
	for (UINT i = 0; i < (UINT)EComponentType::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)EComponentType::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalUpdate();
	}
}

void GameObject::Render()
{
	((MeshRender*)m_arrCom[(UINT)EComponentType::MESHRENDER])->Render();

}

void GameObject::AddComponent(Component * _pCom)
{
	// GameObject 가 해당 컴포넌트를 이미 가지고 있는 경우
	assert(!m_arrCom[(UINT)_pCom->GetCompnentType()]);

	m_arrCom[(UINT)_pCom->GetCompnentType()] = _pCom;
	_pCom->SetGameObject(this);

}


