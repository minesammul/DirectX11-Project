#include "stdafx.h"
#include "Terrain.h"

#include "ResMgr.h"
#include "Mesh.h"

#include "MeshRender.h"


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
			vecIdx.push_back((x + m_iXFaceCount * z) + m_iXFaceCount);
			vecIdx.push_back((x + m_iXFaceCount * z) + 1);
			vecIdx.push_back((x + m_iXFaceCount * z));

			vecIdx.push_back((x + m_iXFaceCount * z) + 1);
			vecIdx.push_back((x + m_iXFaceCount * z) + m_iXFaceCount);
			vecIdx.push_back((x + m_iXFaceCount * z) + m_iXFaceCount + 1);
		}
	}

	CResPtr<CMesh> pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(UINT), vecIdx.size(), &vecIdx[0]);

	CResMgr::GetInst()->AddRes(L"TerrainRect", pMesh);

	MeshRender()->SetMesh(pMesh);
}

void CTerrain::SaveToScene(FILE * _pFile)
{

}

void CTerrain::LoadFromScene(FILE * _pFile)
{

}

