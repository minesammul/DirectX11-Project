#include "stdafx.h"
#include "Terrain.h"

#include "MeshRender.h"
#include "ResMgr.h"
#include "Material.h"
#include "Transform.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "KeyMgr.h"

CTerrain::CTerrain()
	: CComponent(COMPONENT_TYPE::TERRAIN)
	, m_eMod(TERRAIN_MOD::END)
	, m_vBrushScale(Vec2(0.1f, 0.1f))
	, m_iBrushIdx(0)
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
	Vec4 vScale = Vec4(Transform()->GetLocalScale());
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::VEC4_0, &vScale);

	ModCheck();

	KeyCheck();
}
