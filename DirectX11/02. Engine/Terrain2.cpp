#include "stdafx.h"
#include "Terrain.h"

#include "ResMgr.h"
#include "Mesh.h"

#include "MeshRender.h"

#include "Shader.h"
#include "Material.h"

void CTerrain::SetFaceCount(UINT _iXFace, UINT _iZFace)
{
	m_iXFaceCount = _iXFace;
	m_iZFaceCount = _iZFace;

	vector<VTX> vecVtx;	VTX v;
	vector<UINT> vecIdx;

	for (UINT z = 0; z < m_iZFaceCount + 1; ++z)
	{
		for (UINT x = 0; x < m_iXFaceCount + 1; ++x)
		{
			v.vPos = Vec3(x, 0.f, z);
			v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
			v.vNormal = Vec3(0.f, 1.f, 0.f);
			v.vTangent = Vec3(1.f, 0.f, 0.f);
			v.vBinormal = Vec3(0.f, 0.f, 1.f);

			v.vUV = Vec2(x, m_iZFaceCount - z);
			vecVtx.push_back(v);
		}
	}

	// 0	 1---2
	// | \	  \  |
	// 2---1    0
	for (UINT z = 0; z < m_iZFaceCount; ++z)
	{
		for (UINT x = 0; x < m_iXFaceCount; ++x)
		{
			vecIdx.push_back((x + (m_iXFaceCount + 1)  * z) + (m_iXFaceCount + 1));
			vecIdx.push_back((x + (m_iXFaceCount + 1) * z) + 1);
			vecIdx.push_back((x + (m_iXFaceCount + 1) * z));

			vecIdx.push_back((x + (m_iXFaceCount + 1) * z) + 1);
			vecIdx.push_back((x + (m_iXFaceCount + 1) * z) + (m_iXFaceCount + 1));
			vecIdx.push_back((x + (m_iXFaceCount + 1) * z) + (m_iXFaceCount + 1) + 1);
		}
	}

	CResPtr<CMesh> pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(UINT), vecIdx.size(), &vecIdx[0]);

	CResMgr::GetInst()->AddRes(L"TerrainRect", pMesh);

	MeshRender()->SetMesh(pMesh);
}

void CTerrain::CreateComputeShader()
{
	// =========================
	// HeightMap Compute Shader
	// =========================
	CShader* pShader = nullptr;

	pShader = new CShader;
	pShader->CreateComputeShader(L"Shader\\compute.fx", "CS_HeightMap", 5, 0);
	CResMgr::GetInst()->AddRes<CShader>(L"CS_HeightMap", pShader);


	m_pHeightMapMtrl = new CMaterial;
	m_pHeightMapMtrl->SaveDisable();
	m_pHeightMapMtrl->SetShader(pShader);
	CResMgr::GetInst()->AddRes<CMaterial>(L"HeightMapMtrl", m_pHeightMapMtrl);

	m_pHeightMapMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pHeightMap);
	m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[0]);
	m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_1, &m_vecBrush[1]);

	int width = m_pHeightMap->GetWidth();
	int height = m_pHeightMap->GetHeight();

	m_pHeightMapMtrl->SetData(SHADER_PARAM::INT_0, &width);
	m_pHeightMapMtrl->SetData(SHADER_PARAM::INT_1, &height);

	// ======================
	// Picking Compute Shader
	// ======================
	pShader = new CShader;
	pShader->CreateComputeShader(L"Shader\\compute.fx", "CS_Picking", 5, 0);
	CResMgr::GetInst()->AddRes<CShader>(L"CS_Picking", pShader);

	m_pPickMtrl = new CMaterial;
	m_pPickMtrl->SaveDisable();
	m_pPickMtrl->SetShader(pShader);

	m_pPickMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pOutput);

}

void CTerrain::LoadResource()
{
	// HeightMap 만들기
	m_pHeightMap = CResMgr::GetInst()->CreateTexture(L"TerrainHeightMap"
		, 1024, 1024
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS
		, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R32G32B32A32_FLOAT);

	// Picking Output Texture 만들기
	m_pOutput = CResMgr::GetInst()->CreateTexture(L"PickingOutput"
		, 1, 1
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS
		, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R32G32B32A32_FLOAT);

	// Brush Texture
	m_vecBrush.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Brush\\Brush_01.png"));
	m_vecBrush.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Brush\\Brush_02.png"));

	CreateComputeShader();

	// Mesh
	SetFaceCount(m_iXFaceCount, m_iZFaceCount);

	// Material
	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TerrainMtrl"));
	CResPtr<CTexture> pTexture0 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01.tga");
	CResPtr<CTexture> pTexture1 = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01_N.tga");


	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTexture0);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &pTexture1);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_2, &m_pHeightMap);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);

}

void CTerrain::SaveToScene(FILE * _pFile)
{

}

void CTerrain::LoadFromScene(FILE * _pFile)
{

}

