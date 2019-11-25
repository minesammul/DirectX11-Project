#include "stdafx.h"
#include "Light3D.h"

#include "RenderMgr.h"
#include "Transform.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
{
}

CLight3D::~CLight3D()
{
}

void CLight3D::finalupdate()
{
	m_tInfo.vPos = Transform()->GetWorldPos();

	CRenderMgr::GetInst()->RegisterLight3D(this);
}

void CLight3D::render()
{
}

void CLight3D::SetLightType(LIGHT_TYPE _eType)
{
	m_tInfo.iType = (UINT)_eType;	
}
