#include "stdafx.h"
#include "ResourceMgr.h"

#include "Mesh.h"
#include "Shader.h"

ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
}

void ResourceMgr::Init()
{
	CreateDefaultMesh();
	CreateDefaultShader();
}

void ResourceMgr::CreateDefaultMesh()
{
	// ==========
	// Rect Mesh
	// ==========
	std::vector<TVertex> vecVtx;	
	TVertex v;
	std::vector<WORD> vecIdx;

	v.f3Position = DirectX::XMFLOAT3(-0.5f, 0.5f, 0.f);
	v.f4Color = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.f3Position = DirectX::XMFLOAT3(0.5f, 0.5f, 0.f);
	v.f4Color = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.f3Position = DirectX::XMFLOAT3(-0.5f, -0.5f, 0.f);
	v.f4Color = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.f3Position = DirectX::XMFLOAT3(0.5f, -0.5f, 0.f);
	v.f4Color = DirectX::XMFLOAT4(0.5f, 0.5f, 0.f, 1.f);
	vecVtx.push_back(v);

	// Create Index Buffer
	vecIdx.push_back(0);
	vecIdx.push_back(3);
	vecIdx.push_back(2);
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(3);

	Mesh* pMesh = new Mesh;
	pMesh->CreateMesh(sizeof(TVertex), 4, D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(WORD), 6, &vecIdx[0]);

	pMesh->SetName(L"RectMesh");
	m_mapRes[(UINT)EResourceType::MESH].insert(std::make_pair(L"RectMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();

	// ===========
	// Circle Mesh
	// ===========
	UINT iSliceCount = 40;
	float fThetaStride = DirectX::XM_2PI / (float)iSliceCount;
	float fTheta = 0.f;

	// 원의 중심
	v.f3Position = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	v.f4Color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	// 테두리 정점
	for (UINT i = 0; i < iSliceCount + 1; ++i)
	{
		v.f3Position.x = cosf(fTheta);
		v.f3Position.y = sinf(fTheta);
		v.f3Position.z = 0.f;

		v.f4Color = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);

		vecVtx.push_back(v);

		fTheta += fThetaStride;
	}

	// 인덱스
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new Mesh;
	pMesh->CreateMesh(sizeof(TVertex), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(WORD), vecIdx.size(), &vecIdx[0]);

	pMesh->SetName(L"CircleMesh");
	m_mapRes[(UINT)EResourceType::MESH].insert(std::make_pair(L"CircleMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();

}

void ResourceMgr::CreateDefaultShader()
{
	// ==============
	// Default Shader
	// ==============
	Shader* pShader = nullptr;

	pShader = new Shader;
	pShader->CreateVertexShader(L"Engine\\VertexShader.hlsl", "main", 5, 0);
	pShader->CreatePixelShader(L"Engine\\PixelShader.hlsl", "main", 5, 0);

	pShader->SetName(L"DefaultShader");
	m_mapRes[(UINT)EResourceType::SHADER].insert(std::make_pair(L"DefaultShader", pShader));

}
