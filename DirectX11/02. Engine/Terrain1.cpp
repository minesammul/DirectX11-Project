#include "stdafx.h"
#include "Terrain.h"

#include "MeshRender.h"
#include "ResMgr.h"
#include "Material.h"
#include "Transform.h"

#include "KeyMgr.h"
CTerrain::CTerrain()
	: CComponent(COMPONENT_TYPE::TERRAIN)
{
}

CTerrain::~CTerrain()
{
}

void CTerrain::init(UINT _iXFace, UINT _iZFace)
{	
	m_iXFaceCount = _iXFace;
	m_iZFaceCount = _iZFace;

	LoadResource();

	// Transform
	Transform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
}

void CTerrain::finalupdate()
{
	//Vec4 vScale = Vec4(Transform()->GetLocalScale());
	//MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::VEC4_0, &vScale);

	if (KEYHOLD(KEY_TYPE::KEY_UP))
	{
		Vec2 vPos = Vec2(0.5f, 0.5f);
		Vec2 vScale = Vec2(0.4f, 0.4f);

		m_pHeightMapMtrl->SetData(SHADER_PARAM::VEC2_0, &vPos);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::VEC2_1, &vScale);

		m_pHeightMapMtrl->ExcuteComputeShader(1, 1024, 1);
	}
}
