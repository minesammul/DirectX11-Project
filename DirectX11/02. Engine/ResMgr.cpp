#include "stdafx.h"
#include "ResMgr.h"

#include "RenderMgr.h"
#include "Collider2D.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	CCollider2D::ClearMaterial();
	
	// Clone ����
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Vec(m_vecCloneRes[i]);
	}

	// ���� ���ҽ� ����
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Map(m_mapRes[i]);
	}
}

void CResMgr::init()
{
	CreateDefaultMesh();

	CreateDefaultShader();

	CreateDefaultMaterial();
}

void CResMgr::CreateDefaultMesh()
{
	// ==========
	// Rect Mesh
	// ==========
	vector<VTX> vecVtx;	VTX v;
	vector<WORD> vecIdx;

	// 0 --- 1
	// |  \  |
	// 2-----3

	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.5f, 0.5f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	// Create Index Buffer
	vecIdx.push_back(0); 
	vecIdx.push_back(3);
	vecIdx.push_back(2);
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(3);

	CMesh* pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(WORD), vecIdx.size(), &vecIdx[0]);

	pMesh->SetName(L"RectMesh");
	m_mapRes[(UINT)RES_TYPE::MESH].insert(make_pair(L"RectMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();

	// ===================
	// Collider Rect Mesh
	// ===================
	// 0 --- 1
	// |	 |
	// 2-----3

	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.5f, 0.5f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	// Create Index Buffer
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(3);
	vecIdx.push_back(2);
	vecIdx.push_back(0);

	pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(WORD), vecIdx.size(), &vecIdx[0], D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	pMesh->SetName(L"ColliderRectMesh");
	m_mapRes[(UINT)RES_TYPE::MESH].insert(make_pair(L"ColliderRectMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();
	
	// ===========
	// Circle Mesh
	// ===========
	UINT iSliceCount = 40;
	float fThetaStride = XM_2PI / (float)iSliceCount;
	float fTheta = 0.f;
	
	// ���� �߽�
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	// �׵θ� ����
	for (UINT i = 0; i < iSliceCount + 1; ++i)
	{
		v.vPos.x = cosf(fTheta);
		v.vPos.y = sinf(fTheta);
		v.vPos.z = 0.f;

		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

		vecVtx.push_back(v);

		fTheta += fThetaStride;
	}

	// �ε���
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(WORD), vecIdx.size(), &vecIdx[0]);

	pMesh->SetName(L"CircleMesh");
	m_mapRes[(UINT)RES_TYPE::MESH].insert(make_pair(L"CircleMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();
}

void CResMgr::CreateDefaultShader()
{
	wstring strKey;

	// ===================
	// Vertex Color Shader
	// ===================
	CShader* pShader = nullptr;

	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS", 5, 0);

	strKey = L"VtxColorShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	// ===================
	// Collider2D Shader
	// ===================	
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_Collider2D", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_Collider2D", 5, 0);

	pShader->AddParam(SHADER_PARAM::INT_0, L"Collision Check", false);


	strKey = L"Collider2DShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	
	// ==============
	// Texture Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_Tex", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_Tex", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");

	strKey = L"TextureShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));
		

	// ==============
	// Std2D Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_Std2D", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_Std2D", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");
	
	//dgkim Start
	//Shader Parameter test�뵵�� ���� �ڵ� 
	pShader->AddParam(SHADER_PARAM::VEC4_0, L"test vec4_0");
	pShader->AddParam(SHADER_PARAM::MAT_0, L"test MAT_0");
	//dgkim End

	strKey = L"Std2DShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	// ====================
	// Shadow Effect Shader
	// ====================
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\effect.fx", "VS_2DShadow", 5, 0);
	pShader->CreatePixelShader(L"Shader\\effect.fx", "PS_2DShadow", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");

	strKey = L"2DShdowShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));
}

void CResMgr::CreateDefaultMaterial()
{
	CResPtr<CMaterial> pMtrl = nullptr;

	pMtrl = new CMaterial;
	pMtrl->SetName(L"VtxColorMtrl");
	pMtrl->SetShader(FindRes<CShader>(L"VtxColorShader"));
	AddRes<CMaterial>(pMtrl->GetName(), pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetName(L"Collider2DMtrl");
	pMtrl->SetShader(FindRes<CShader>(L"Collider2DShader"));
	AddRes<CMaterial>(pMtrl->GetName(), pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetName(L"TextureMtrl");
	pMtrl->SetShader(FindRes<CShader>(L"TextureShader"));
	AddRes<CMaterial>(pMtrl->GetName(), pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetName(L"Std2DMtrl");
	pMtrl->SetShader(FindRes<CShader>(L"Std2DShader"));
	AddRes<CMaterial>(pMtrl->GetName(), pMtrl);

	//pMtrl = new CMaterial;
	//pMtrl->SetName(L"2DShadowMtrl");
	//pMtrl->SetShader(FindRes<CShader>(L"2DShdowShader"));
	//AddRes<CMaterial>(pMtrl->GetName(), pMtrl);	

	CCollider2D::CreateMaterial();
}

void CResMgr::AddRes(RES_TYPE _eType, CResource * _pResource)
{
	map<wstring, CResource*>::iterator iter = m_mapRes[(UINT)_eType].find(_pResource->GetName());

	if (iter != m_mapRes[(UINT)_eType].end())
		return;

	m_mapRes[(UINT)_eType].insert(make_pair(_pResource->GetName(), _pResource));
}
