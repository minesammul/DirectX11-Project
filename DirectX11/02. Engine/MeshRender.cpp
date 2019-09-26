#include "stdafx.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Transform.h"

#include "Collider2D.h"
#include "Animator2D.h"
#include "Animation2D.h"
#include "ResMgr.h"

CMeshRender::CMeshRender()
	: m_pMesh(nullptr)
	, m_pMtrl(nullptr)
	, CComponent(COMPONENT_TYPE::MESHRENDER)
{	
}

CMeshRender::~CMeshRender()
{
}

CResPtr<CMaterial> CMeshRender::GetCloneMaterial()
{
	if (nullptr == m_pMtrl)
		return nullptr;	
	   
	m_pMtrl = m_pMtrl->Clone();

	CResMgr::GetInst()->AddCloneRes(m_pMtrl);

	return m_pMtrl;
}

void CMeshRender::update()
{
}

void CMeshRender::render()
{	
	Transform()->UpdateData();

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		CAnimation2D::ClearRegister();
	}

	if (m_pMtrl->GetShader() == nullptr)
	{
		return;
	}

	m_pMtrl->UpdateData();
	m_pMesh->SetLayout(m_pMtrl->GetShader());	
	m_pMesh->render();

	// Collider 가 있으면 그려준다.
	if (nullptr != Collider2D())
		Collider2D()->render();
}	
