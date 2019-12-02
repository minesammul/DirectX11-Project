#include "stdafx.h"
#include "Terrain.h"

#include "MeshRender.h"
#include "ResMgr.h"
#include "Material.h"
#include "Transform.h"

CTerrain::CTerrain()
	: CComponent(COMPONENT_TYPE::TERRAIN)
{
}

CTerrain::~CTerrain()
{
}

void CTerrain::init(UINT _iXFace, UINT _iZFace)
{
	// Mesh
	SetFaceCount(_iXFace, _iZFace);

	// Material
	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"));

	// Transform
	Transform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
}

void CTerrain::finalupdate()
{
}
