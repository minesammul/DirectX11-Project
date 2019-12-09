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
	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TerrainMtrl"));
	CResPtr<CTexture> pTexture0 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01.tga");
	CResPtr<CTexture> pTexture1 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01_N.tga");
	CResPtr<CTexture> pTexture2 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\HeightMap\\HeightMap_01.png");

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTexture0);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &pTexture1);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_2, &pTexture2);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);


	// Transform
	Transform()->SetLocalScale(Vec3(100.f, 1000.f, 100.f));
}

void CTerrain::finalupdate()
{
}
