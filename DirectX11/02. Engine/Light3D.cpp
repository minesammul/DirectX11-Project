#include "stdafx.h"
#include "Light3D.h"

#include "ResMgr.h"
#include "RenderMgr.h"
#include "Transform.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
	, m_pMtrl(nullptr)
	, m_iIdx(-1)
{
}

CLight3D::~CLight3D()
{
}

void CLight3D::finalupdate()
{
	m_tInfo.vPos = Transform()->GetWorldPos();
	m_iIdx = CRenderMgr::GetInst()->RegisterLight3D(this);
}

void CLight3D::render()
{
	m_pMtrl->SetData(SHADER_PARAM::INT_0, &m_iIdx);
	m_pMtrl->UpdateData();
	m_pMesh->SetLayout(m_pMtrl->GetShader());
	m_pMesh->render();
}

void CLight3D::SetLightType(LIGHT_TYPE _eType)
{
	m_tInfo.iType = (UINT)_eType;

	if ((UINT)LIGHT_TYPE::DIRECTIONAL == m_tInfo.iType)
	{
		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"DirLightMtrl");
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	}
	else if ((UINT)LIGHT_TYPE::POINT == m_tInfo.iType)
	{
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PointLightMtrl");
	}
	else
	{

	}
}
