#include "stdafx.h"
#include "Terrain.h"

#include "ResMgr.h"
#include "Mesh.h"

#include "MeshRender.h"

#include "Shader.h"
#include "Material.h"
#include "KeyMgr.h"
#include "Camera.h"
#include "Transform.h"

void CTerrain::ModCheck()
{
	if (KEYTAB(KEY_TYPE::KEY_NUM1))
	{
		m_eMod = TERRAIN_MOD::HEIGHTMAP;
	}
	else if (KEYTAB(KEY_TYPE::KEY_NUM2))
	{
		m_eMod = TERRAIN_MOD::SPLATTING;
	}
	else if (KEYTAB(KEY_TYPE::KEY_NUM3))
	{
		m_eMod = TERRAIN_MOD::END;
	}
}

void CTerrain::KeyCheck()
{
	Vec2 vPos = Vec2(0.f, 0.f);
	int iPicking = 0;

	if (m_eMod == TERRAIN_MOD::END || !Picking(vPos))
	{
		// Brush Texture 를 셋팅하지 않아서,  Terrain 에서 Brush 자국이 보이지 않게 한다.
		CResPtr<CTexture> pTex = nullptr;
		MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_3, &pTex);
		return;
	}

	// 피킹 성공
	CResPtr<CMaterial> pMtrl = MeshRender()->GetSharedMaterial();
	pMtrl->SetData(SHADER_PARAM::TEX_3, &m_vecBrush[m_iBrushIdx]);
	pMtrl->SetData(SHADER_PARAM::VEC2_0, &vPos);
	pMtrl->SetData(SHADER_PARAM::VEC2_1, &m_vBrushScale);

	if (KEYHOLD(KEY_TYPE::KEY_LBTN))
	{
		// 지형 수정모드(height, splatting)
		if (m_eMod == TERRAIN_MOD::HEIGHTMAP)
		{
			m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[m_iBrushIdx]);
			m_pHeightMapMtrl->SetData(SHADER_PARAM::VEC2_0, &vPos);
			m_pHeightMapMtrl->SetData(SHADER_PARAM::VEC2_1, &m_vBrushScale);
			m_pHeightMapMtrl->ExcuteComputeShader(1, 1024, 1);
		}
		else if (m_eMod == TERRAIN_MOD::SPLATTING)
		{

		}
	}
}

int CTerrain::Picking(Vec2 & _vPos)
{
	tRay ray = m_pToolCam->GetRay();

	Matrix matWorldInv = Transform()->GetWorldMat();
	matWorldInv = XMMatrixInverse(nullptr, matWorldInv);

	Vec4 vStart = XMVector3TransformCoord(ray.vStart, matWorldInv);
	Vec4 vDir = XMVector3TransformNormal(ray.vDir, matWorldInv);
	vDir.Normalize();

	m_pPickMtrl->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
	m_pPickMtrl->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);
	m_pPickMtrl->SetData(SHADER_PARAM::VEC4_0, &vStart);
	m_pPickMtrl->SetData(SHADER_PARAM::VEC4_1, &vDir);

	int iXGroup = (m_iXFaceCount * 2) / 32;
	int iYGroup = m_iZFaceCount / 32;

	if ((m_iXFaceCount * 2) % 32 != 0)
		iXGroup += 1;
	if (m_iZFaceCount % 32)
		iYGroup += 1;

	// Picking coputeshader 계산
	m_pOutput->RWClear(Vec4(0.f, 0.f, 0.f, 0.f));

	m_pPickMtrl->ExcuteComputeShader(iXGroup, iYGroup, 1);

	m_pOutput->Capture();
	Vec4* pData = (Vec4*)m_pOutput->GetSysMem();

	// 피킹 실패
	if (pData->w == 0.f)
		return 0;

	// 픽킹 위치를 비율로 전환
	_vPos = Vec2(pData->x / (float)m_iXFaceCount, 1.f - (pData->z / (float)m_iZFaceCount));

	return 1;
}

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
	CResMgr::GetInst()->AddRes<CMaterial>(L"PickingMtrl", m_pPickMtrl);

	m_pPickMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pOutput);

}

void CTerrain::LoadResource()
{
	// HeightMap 만들기
	m_pHeightMap = CResMgr::GetInst()->CreateTexture(L"TerrainHeightMap"
		, m_iXFaceCount * 16, m_iZFaceCount * 16
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS
		, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_pWeightTex = CResMgr::GetInst()->CreateTexture(L"TerrainWeightTex"
		, m_iXFaceCount * 16, m_iZFaceCount * 16
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
	// Tile Texture
	//vector<CResPtr<CTexture>> vecTex;
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01.tga"));
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_02.tga"));
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_03.tga"));
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_04.png"));
	//pTileArrTex->Save(pTileArrTex->GetName());

	//vecTex.clear();
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_01_N.tga"));
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_02_N.tga"));
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_03_N.tga"));
	//vecTex.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_04_N.png"));
	//CResPtr<CTexture> pTileArrNomalTex = CResMgr::GetInst()->CreateArrayTexture(L"Texture\\Tile\\TILE_ARR_N.dds", vecTex);
	//pTileArrNomalTex->Save(pTileArrNomalTex->GetName());

	CResPtr<CTexture> pTileArrTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_ARR.dds");
	CResPtr<CTexture> pTileArrNormalTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_ARR_N.dds");

	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TerrainMtrl"));
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_ARR_0, &pTileArrTex);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_ARR_1, &pTileArrNormalTex);
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

