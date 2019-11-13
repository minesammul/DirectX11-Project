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
	
	// Clone 삭제
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Vec(m_vecCloneRes[i]);
	}

	// 원본 리소스 삭제
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
	vector<UINT> vecIdx;

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
		, sizeof(UINT), vecIdx.size(), &vecIdx[0]);

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
		, sizeof(UINT), vecIdx.size(), &vecIdx[0], D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

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
	
	// 원의 중심
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	// 테두리 정점
	for (UINT i = 0; i < iSliceCount + 1; ++i)
	{
		v.vPos.x = cosf(fTheta);
		v.vPos.y = sinf(fTheta);
		v.vPos.z = 0.f;

		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

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

	pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(UINT), vecIdx.size(), &vecIdx[0]);

	pMesh->SetName(L"CircleMesh");
	m_mapRes[(UINT)RES_TYPE::MESH].insert(make_pair(L"CircleMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();

	// =========
// Cube Mesh
// =========
	VTX arrCube[24] = {};

	// 윗면
	arrCube[0].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[0].vUV = Vec2(0.f, 0.f);
	arrCube[0].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[1].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[1].vUV = Vec2(0.f, 0.f);
	arrCube[1].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[2].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[2].vUV = Vec2(0.f, 0.f);
	arrCube[2].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[3].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[3].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[3].vUV = Vec2(0.f, 0.f);
	arrCube[3].vNormal = Vec3(0.f, 1.f, 0.f);


	// 아랫 면	
	arrCube[4].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[4].vUV = Vec2(0.f, 0.f);
	arrCube[4].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[5].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[5].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[5].vUV = Vec2(0.f, 0.f);
	arrCube[5].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[6].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[6].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[6].vUV = Vec2(0.f, 0.f);
	arrCube[6].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[7].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[7].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[7].vUV = Vec2(0.f, 0.f);
	arrCube[7].vNormal = Vec3(0.f, -1.f, 0.f);

	// 왼쪽 면
	arrCube[8].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[8].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[8].vUV = Vec2(0.f, 0.f);
	arrCube[8].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[9].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[9].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[9].vUV = Vec2(0.f, 0.f);
	arrCube[9].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[10].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[10].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[10].vUV = Vec2(0.f, 0.f);
	arrCube[10].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[11].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[11].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[11].vUV = Vec2(0.f, 0.f);
	arrCube[11].vNormal = Vec3(-1.f, 0.f, 0.f);

	// 오른쪽 면
	arrCube[12].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[12].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[12].vUV = Vec2(0.f, 0.f);
	arrCube[12].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[13].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[13].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[13].vUV = Vec2(0.f, 0.f);
	arrCube[13].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[14].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[14].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[14].vUV = Vec2(0.f, 0.f);
	arrCube[14].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[15].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[15].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[15].vUV = Vec2(0.f, 0.f);
	arrCube[15].vNormal = Vec3(1.f, 0.f, 0.f);

	// 앞 면
	arrCube[16].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[16].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[16].vUV = Vec2(0.f, 0.f);
	arrCube[16].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[17].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[17].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[17].vUV = Vec2(0.f, 0.f);
	arrCube[17].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[18].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[18].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[18].vUV = Vec2(0.f, 0.f);
	arrCube[18].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[19].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[19].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[19].vUV = Vec2(0.f, 0.f);
	arrCube[19].vNormal = Vec3(0.f, 0.f, 1.f);

	// 뒷 면
	arrCube[20].vPos = Vec3(-0.5f, 0.5f, -0.5f);;
	arrCube[20].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[20].vUV = Vec2(0.f, 0.f);
	arrCube[20].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[21].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[21].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[21].vUV = Vec2(0.f, 0.f);
	arrCube[21].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[22].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[22].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[22].vUV = Vec2(0.f, 0.f);
	arrCube[22].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[23].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[23].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[23].vUV = Vec2(0.f, 0.f);
	arrCube[23].vNormal = Vec3(0.f, 0.f, -1.f);

	// 인덱스
	for (int i = 0; i < 12; i += 2)
	{
		vecIdx.push_back(i * 2);
		vecIdx.push_back(i * 2 + 1);
		vecIdx.push_back(i * 2 + 2);

		vecIdx.push_back(i * 2);
		vecIdx.push_back(i * 2 + 2);
		vecIdx.push_back(i * 2 + 3);
	}

	pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), 24, D3D11_USAGE_DEFAULT, arrCube
		, sizeof(UINT), vecIdx.size(), &vecIdx[0]);

	pMesh->SetName(L"CubeMesh");
	m_mapRes[(UINT)RES_TYPE::MESH].insert(make_pair(L"CubeMesh", pMesh));

	vecVtx.clear();
	vecIdx.clear();

	// ============
// Sphere Mesh
// ============

	float fRadius = 1.f;

	// Top
	v.vPos = Vec3(0.f, fRadius, 0.f);
	v.vUV = Vec2(0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vNormal = v.vPos;
	v.vNormal.Normalize();
	//v.vTangent = Vec3(1.f, 0.f, 0.f);
	//v.vBinormal = Vec3(0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	// Body
	UINT iStackCount = 20; // 가로 분할 개수
	iSliceCount = 20; // 세로 분할 개수

	float fStackAngle = XM_PI / iStackCount;
	float fSliceAngle = XM_2PI / iSliceCount;

	float fUVXStep = 1.f / (float)iSliceCount;
	float fUVYStep = 1.f / (float)iStackCount;

	for (UINT i = 1; i < iStackCount; ++i)
	{
		float phi = i * fStackAngle;

		for (UINT j = 0; j <= iSliceCount; ++j)
		{
			float theta = j * fSliceAngle;

			v.vPos = Vec3(fRadius * sinf(i * fStackAngle) * cosf(j * fSliceAngle)
				, fRadius * cosf(i * fStackAngle)
				, fRadius * sinf(i * fStackAngle) * sinf(j * fSliceAngle));
			v.vUV = Vec2(fUVXStep * j, fUVYStep * i);
			v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
			v.vNormal = v.vPos;
			v.vNormal.Normalize();

			//v.vTangent.x = -fRadius * sinf(phi) * sinf(theta);
			//v.vTangent.y = 0.f;
			//v.vTangent.z = fRadius * sinf(phi) * cosf(theta);
			//v.vTangent.Normalize();

			//v.vTangent.Cross(v.vNormal, v.vBinormal);
			//v.vBinormal.Normalize();

			vecVtx.push_back(v);
		}
	}

	// Bottom
	v.vPos = Vec3(0.f, -fRadius, 0.f);
	v.vUV = Vec2(0.5f, 1.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vNormal = v.vPos;
	v.vNormal.Normalize();

	//v.vTangent = Vec3(1.f, 0.f, 0.f);
	//v.vBinormal = Vec3(0.f, 0.f, -1.f);
	vecVtx.push_back(v);

	// 인덱스
	// 북극점
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// 몸통
	for (UINT i = 0; i < iStackCount - 2; ++i)
	{
		for (UINT j = 0; j < iSliceCount; ++j)
		{
			// + 
			// | \
			// +--+
			vecIdx.push_back((iSliceCount + 1) * (i)+(j)+1);
			vecIdx.push_back((iSliceCount + 1) * (i + 1) + (j + 1) + 1);
			vecIdx.push_back((iSliceCount + 1) * (i + 1) + (j)+1);

			// +--+
			//  \ |
			//    +
			vecIdx.push_back((iSliceCount + 1) * (i)+(j)+1);
			vecIdx.push_back((iSliceCount + 1) * (i)+(j + 1) + 1);
			vecIdx.push_back((iSliceCount + 1) * (i + 1) + (j + 1) + 1);
		}
	}

	// 남극점
	UINT iBottomIdx = vecVtx.size() - 1;
	for (UINT i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(iBottomIdx);
		vecIdx.push_back(iBottomIdx - (i + 2));
		vecIdx.push_back(iBottomIdx - (i + 1));
	}

	pMesh = new CMesh;
	pMesh->CreateMesh(sizeof(VTX), vecVtx.size(), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, sizeof(UINT), vecIdx.size(), &vecIdx[0]);

	pMesh->SetName(L"SphereMesh");
	m_mapRes[(UINT)RES_TYPE::MESH].insert(make_pair(L"SphereMesh", pMesh));

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
	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
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
	// Texture UV Animation Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_TexUV", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_TexUV", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");
	pShader->AddParam(SHADER_PARAM::FLOAT_0, L"U Value");
	pShader->AddParam(SHADER_PARAM::FLOAT_1, L"V Value");
	pShader->AddParam(SHADER_PARAM::VEC4_0, L"Color Mul Value");

	strKey = L"TextureUVAnimationShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	// ==============
	// Fade In-Out Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_Fade", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_Fade", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");
	pShader->AddParam(SHADER_PARAM::FLOAT_0, L"Alpha Value");

	strKey = L"FadeInOutShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	// ==============
	// Inverse Image 2D Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_Inverse2D", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_Inverse2D", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");
	pShader->AddParam(SHADER_PARAM::INT_0, L"Inverse On Off");

	strKey = L"InverseImage2DShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	// ==============
	// Inverse AfterImage 2D Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std.fx", "VS_InverseAfterImage2D", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std.fx", "PS_InverseAfterImage2D", 5, 0);

	pShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	pShader->AddParam(SHADER_PARAM::TEX_0, L"Output Image");
	pShader->AddParam(SHADER_PARAM::INT_0, L"Inverse On Off");
	pShader->AddParam(SHADER_PARAM::FLOAT_0, L"Inverse On Off");

	strKey = L"InverseAfterImage2DShader";
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

	// ==============
	// Gouraud Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std3d.fx", "VS_Gouraud", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std3d.fx", "PS_Gouraud", 5, 0);

	strKey = L"GouraudShader";
	pShader->SetName(strKey);
	m_mapRes[(UINT)RES_TYPE::SHADER].insert(make_pair(strKey, pShader));

	// ==============
	// Phong Shader
	// ==============
	pShader = new CShader;
	pShader->CreateVertexShader(L"Shader\\std3d.fx", "VS_Phong", 5, 0);
	pShader->CreatePixelShader(L"Shader\\std3d.fx", "PS_Phong", 5, 0);

	strKey = L"PhongShader";
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

	pMtrl = new CMaterial;
	pMtrl->SetName(L"Material\\Gouraud.mtrl");
	pMtrl->SetShader(FindRes<CShader>(L"GouraudShader"));
	AddRes<CMaterial>(pMtrl->GetName(), pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetName(L"Material\\Phong.mtrl");
	pMtrl->SetShader(FindRes<CShader>(L"PhongShader"));
	AddRes<CMaterial>(pMtrl->GetName(), pMtrl);

	CCollider2D::CreateMaterial();
}

void CResMgr::AddRes(RES_TYPE _eType, CResource * _pResource)
{
	map<wstring, CResource*>::iterator iter = m_mapRes[(UINT)_eType].find(_pResource->GetName());

	if (iter != m_mapRes[(UINT)_eType].end())
		return;

	m_mapRes[(UINT)_eType].insert(make_pair(_pResource->GetName(), _pResource));
}
