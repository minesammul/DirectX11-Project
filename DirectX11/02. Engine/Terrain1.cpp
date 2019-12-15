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
	// HeightMap ¸¸µé±â
	m_pHeightMap = CResMgr::GetInst()->CreateTexture(	L"TerrainHeightMap", 
														1024, 
														1024, 
														D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 
														D3D11_USAGE_DEFAULT, 
														DXGI_FORMAT_R32G32B32A32_FLOAT);

	CreateComputeShader();

	// Mesh
	SetFaceCount(_iXFace, _iZFace);

	// Material
	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TerrainMtrl"));
	CResPtr<CTexture> pTexture0 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01.tga");
	CResPtr<CTexture> pTexture1 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01_N.tga");

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTexture0);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &pTexture1);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_2, &m_pHeightMap);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);


	// Transform
	Transform()->SetLocalScale(Vec3(100.f, 1000.f, 100.f));
}

void CTerrain::finalupdate()
{
	//Vec4 vScale = Vec4(Transform()->GetLocalScale());
	//MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::VEC4_0, &vScale);

	if (KEYTAB(KEY_TYPE::KEY_UP))
	{
		m_pHeightMapMtrl->ExcuteComputeShader(1, 1024, 1);
	}
}
