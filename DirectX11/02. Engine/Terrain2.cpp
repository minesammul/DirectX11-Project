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
#include "SceneMgr.h"
#include "Scene.h"
#include "Device.h"

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
	else if (KEYTAB(KEY_TYPE::KEY_NUM4))
	{
		m_iTileIdx += 1;
		if (m_iTileIdx > 3)
			m_iTileIdx = 0;
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
			m_pWeightMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[m_iBrushIdx]);
			m_pWeightMtrl->SetData(SHADER_PARAM::VEC2_0, &vPos);
			m_pWeightMtrl->SetData(SHADER_PARAM::VEC2_1, &m_vBrushScale);
			m_pWeightMtrl->SetData(SHADER_PARAM::INT_2, &m_iTileIdx);
			m_pWeightMtrl->ExcuteComputeShader(1, 1024, 1);
		}
	}
}

int CTerrain::Picking(Vec2 & _vPos)
{
	if (m_pToolCam == nullptr)
	{
		assert(false && "Terrain ToolCamera is Null");
	}

	SetMaterialParameter();

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

void CTerrain::SetMaterialParameter()
{
	{
		m_pHeightMapMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pHeightMap);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[0]);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_1, &m_vecBrush[1]);
		int width = m_pHeightMap->GetWidth();
		int height = m_pHeightMap->GetHeight();

		m_pHeightMapMtrl->SetData(SHADER_PARAM::INT_0, &width);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::INT_1, &height);
	}

	{
		m_pWeightMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pWeightTex);
		m_pWeightMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[0]);
		m_pWeightMtrl->SetData(SHADER_PARAM::TEX_1, &m_vecBrush[1]);

		int width = m_pWeightTex->GetWidth();
		int height = m_pWeightTex->GetHeight();

		m_pWeightMtrl->SetData(SHADER_PARAM::INT_0, &width);
		m_pWeightMtrl->SetData(SHADER_PARAM::INT_1, &height);
		m_pWeightMtrl->SetData(SHADER_PARAM::INT_2, &m_iTileIdx);
	}

	{
		m_pPickMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pOutput);
	}


	// Material
	CResPtr<CTexture> pTileArrTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_ARR.dds");
	CResPtr<CTexture> pTileArrNormalTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_ARR_N.dds");

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_ARR_0, &pTileArrTex);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_ARR_1, &pTileArrNormalTex);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &m_pWeightTex);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_2, &m_pHeightMap);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);

}

void CTerrain::LoadResource()
{

	m_pHeightMap = CResMgr::GetInst()->FindRes<CTexture>(L"TerrainHeightMap");

	m_pWeightTex = CResMgr::GetInst()->FindRes<CTexture>(L"TerrainWeightTex");

	m_pOutput = CResMgr::GetInst()->FindRes<CTexture>(L"PickingOutput");


	// Brush Texture
	m_vecBrush.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Brush\\Brush_01.png"));
	m_vecBrush.push_back(CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Brush\\Brush_02.png"));


	{
		m_pHeightMapMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"CS_HeightMapMtrl");

		m_pHeightMapMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pHeightMap);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[0]);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::TEX_1, &m_vecBrush[1]);
		int width = m_pHeightMap->GetWidth();
		int height = m_pHeightMap->GetHeight();

		m_pHeightMapMtrl->SetData(SHADER_PARAM::INT_0, &width);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::INT_1, &height);
	}

	{
		m_pWeightMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"CS_WeightMapMtrl");

		m_pWeightMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pWeightTex);
		m_pWeightMtrl->SetData(SHADER_PARAM::TEX_0, &m_vecBrush[0]);
		m_pWeightMtrl->SetData(SHADER_PARAM::TEX_1, &m_vecBrush[1]);

		int width = m_pWeightTex->GetWidth();
		int height = m_pWeightTex->GetHeight();

		m_pWeightMtrl->SetData(SHADER_PARAM::INT_0, &width);
		m_pWeightMtrl->SetData(SHADER_PARAM::INT_1, &height);
		m_pWeightMtrl->SetData(SHADER_PARAM::INT_2, &m_iTileIdx);
	}

	{
		m_pPickMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"CS_PickingMtrl");

		m_pPickMtrl->SetData(SHADER_PARAM::RWTEX_0, &m_pOutput);
	}

	{
		CResPtr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"TerrainRect");
		MeshRender()->SetMesh(pMesh);
	}


	// Material
	CResPtr<CTexture> pTileArrTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_ARR.dds");
	CResPtr<CTexture> pTileArrNormalTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\TILE_ARR_N.dds");

	MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TerrainMtrl"));
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_ARR_0, &pTileArrTex);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_ARR_1, &pTileArrNormalTex);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &m_pWeightTex);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_2, &m_pHeightMap);

	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);

}

void CTerrain::SaveToScene(FILE * _pFile)
{
	fwrite(&m_iXFaceCount, sizeof(UINT), 1, _pFile);
	fwrite(&m_iZFaceCount, sizeof(UINT), 1, _pFile);
	
	{
		bool bHeightTexture = true;
		bool bHeightMtrl = true;

		if (nullptr == m_pHeightMap)
			bHeightTexture = false;
		if (nullptr == m_pHeightMapMtrl)
			bHeightMtrl = false;

		fwrite(&bHeightTexture, 1, 1, _pFile);
		if (bHeightTexture)
		{
			SaveWString(m_pHeightMap->GetName().c_str(), _pFile);
			SaveWString(m_pHeightMap->GetPath().c_str(), _pFile);
		}

		fwrite(&bHeightMtrl, 1, 1, _pFile);
		if (bHeightMtrl)
		{
			SaveWString(m_pHeightMapMtrl->GetName().c_str(), _pFile);
			SaveWString(m_pHeightMapMtrl->GetPath().c_str(), _pFile);
		}
	}

	{
		bool bWeightTexture = true;
		bool bWeightMtrl = true;

		if (nullptr == m_pWeightTex)
			bWeightTexture = false;
		if (nullptr == m_pWeightMtrl)
			bWeightMtrl = false;

		fwrite(&bWeightTexture, 1, 1, _pFile);
		if (bWeightTexture)
		{
			SaveWString(m_pWeightTex->GetName().c_str(), _pFile);
			SaveWString(m_pWeightTex->GetPath().c_str(), _pFile);
		}

		fwrite(&bWeightMtrl, 1, 1, _pFile);
		if (bWeightMtrl)
		{
			SaveWString(m_pWeightMtrl->GetName().c_str(), _pFile);
			SaveWString(m_pWeightMtrl->GetPath().c_str(), _pFile);
		}
	}

	{
		UINT brushCount = m_vecBrush.size();
		fwrite(&brushCount, sizeof(UINT), 1, _pFile);

		for (UINT index = 0; index < brushCount; index++)
		{
			SaveWString(m_vecBrush[index]->GetName().c_str(), _pFile);
			SaveWString(m_vecBrush[index]->GetPath().c_str(), _pFile);
		}
	}

	{
		bool bOutputTexture = true;

		if (nullptr == m_pOutput)
			bOutputTexture = false;

		fwrite(&bOutputTexture, 1, 1, _pFile);
		if (bOutputTexture)
		{
			SaveWString(m_pOutput->GetName().c_str(), _pFile);
			SaveWString(m_pOutput->GetPath().c_str(), _pFile);
		}
	}

	{
		bool bPickMtrl = true;

		if (nullptr == m_pPickMtrl)
			bPickMtrl = false;

		fwrite(&bPickMtrl, 1, 1, _pFile);
		if (bPickMtrl)
		{
			SaveWString(m_pPickMtrl->GetName().c_str(), _pFile);
			SaveWString(m_pPickMtrl->GetPath().c_str(), _pFile);
		}
	}


	{
		wstring name = m_pHeightMap->GetName();
		name += L".dds";

		wstring path = L"Texture\\Terrain\\";

		wstring savePathWithFile = path + name;
		m_pHeightMap->Capture();
		m_pHeightMap->Save(savePathWithFile);

		path += name;
		SaveWString(path.c_str(), _pFile);
	}

	{
		wstring name = m_pWeightTex->GetName();
		name += L".dds";

		wstring path = L"Texture\\Terrain\\";

		wstring savePathWithFile = path + name;
		m_pWeightTex->Capture();
		m_pWeightTex->Save(savePathWithFile);

		path += name;
		SaveWString(path.c_str(), _pFile);
	}
}

void CTerrain::LoadFromScene(FILE * _pFile)
{
	fread(&m_iXFaceCount, sizeof(UINT), 1, _pFile);
	fread(&m_iZFaceCount, sizeof(UINT), 1, _pFile);

	m_eMod = TERRAIN_MOD::HEIGHTMAP;
	m_vBrushScale = Vec2(0.1f, 0.1f);

	{
		bool bTexture = true;
		bool bMtrl = true;

		wstring strKey, strPath;

		fread(&bTexture, 1, 1, _pFile);
		if (bTexture)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			m_pHeightMap = CResMgr::GetInst()->FindRes<CTexture>(strKey);
			if (nullptr == m_pHeightMap)
			{
				CResMgr::GetInst()->Load<CTexture>(strKey, strPath);
			}
		}

		fread(&bMtrl, 1, 1, _pFile);
		if (bMtrl)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			m_pHeightMapMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strKey);
			if (nullptr == m_pHeightMapMtrl)
			{
				CResMgr::GetInst()->Load<CMaterial>(strKey, strPath);
			}
		}
	}

	{
		bool bTexture = true;
		bool bMtrl = true;

		wstring strKey, strPath;

		fread(&bTexture, 1, 1, _pFile);
		if (bTexture)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			m_pWeightTex = CResMgr::GetInst()->FindRes<CTexture>(strKey);
			if (nullptr == m_pWeightTex)
			{
				CResMgr::GetInst()->Load<CTexture>(strKey, strPath);
			}
		}

		fread(&bMtrl, 1, 1, _pFile);
		if (bMtrl)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			m_pWeightMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strKey);
			if (nullptr == m_pWeightMtrl)
			{
				CResMgr::GetInst()->Load<CMaterial>(strKey, strPath);
			}
		}
	}

	m_iTileIdx = 0;

	{
		UINT brushCount = m_vecBrush.size();
		fread(&brushCount, sizeof(UINT), 1, _pFile);

		for (UINT index = 0; index < brushCount; index++)
		{
			wstring strKey = LoadWString(_pFile);
			wstring strPath = LoadWString(_pFile);


			m_vecBrush.push_back(CResMgr::GetInst()->FindRes<CTexture>(strKey));
		}
	}

	m_iBrushIdx = 0;

	{
		bool bTexture = true;

		wstring strKey, strPath;

		fread(&bTexture, 1, 1, _pFile);
		if (bTexture)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			m_pOutput = CResMgr::GetInst()->FindRes<CTexture>(strKey);
			if (nullptr == m_pOutput)
			{
				CResMgr::GetInst()->Load<CTexture>(strKey, strPath);
			}
		}
	}

	{
		bool bMtrl = true;

		wstring strKey, strPath;

		fread(&bMtrl, 1, 1, _pFile);
		if (bMtrl)
		{
			strKey = LoadWString(_pFile);
			strPath = LoadWString(_pFile);

			m_pPickMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strKey);
			if (nullptr == m_pPickMtrl)
			{
				CResMgr::GetInst()->Load<CMaterial>(strKey, strPath);
			}
		}
	}

	{
		wstring filePath = LoadWString(_pFile);
		CResPtr<CTexture> saveHeightMap = CResMgr::GetInst()->FindRes<CTexture>(filePath);
		CONTEXT->CopyResource(m_pHeightMap->GetTexture2D(), saveHeightMap->GetTexture2D());
	}

	{
		wstring filePath = LoadWString(_pFile);
		CResPtr<CTexture> saveWeightMap = CResMgr::GetInst()->FindRes<CTexture>(filePath);
		CONTEXT->CopyResource(m_pWeightTex->GetTexture2D(), saveWeightMap->GetTexture2D());
	}
}

