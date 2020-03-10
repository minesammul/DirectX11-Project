#include "stdafx.h"
#include "ParticleSystem.h"

#include "StructuredBuffer.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

#include "Transform.h"

CParticleSystem::CParticleSystem()
	: CComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_pParticleBuffer(nullptr)
	, m_pSharedBuffer(nullptr)
	, m_iMaxParticle(10000)
	, m_fFrequency(0.002f)
	, m_fAccTime(0.f)
	, m_fMinLifeTime(0.5f)
	, m_fMaxLifeTime(1.f)
	, m_fMinSpeed(100)
	, m_fMaxSpeed(50.f)
	, m_fStartScale(30.f)
	, m_fEndScale(1.f)
	, m_vStartColor(Vec4(1.0f, 0.6f, 0.1f, 0.8f))
	, m_vEndColor(Vec4(0.1f, 0.1f, 0.1f, 0.2f))
{
	// 구조화 버퍼 생성
	m_pParticleBuffer = new CStructuredBuffer;
	m_pParticleBuffer->Create(sizeof(tParticle), m_iMaxParticle, nullptr);

	m_pSharedBuffer = new CStructuredBuffer;
	m_pSharedBuffer->Create(sizeof(tParticleShared), 1, nullptr);

	// 사각형 Mesh
	m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh");

	// Material
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleMtrl");
	m_pParticleTexture = CResMgr::GetInst()->Load<CTexture>(L"Texture\\Particle\\CartoonSmoke.png", L"Texture\\Particle\\CartoonSmoke.png");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, &m_pParticleTexture);

	// ParticleUpdate
	m_pUpdateMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleUpdateMtrl");
}

CParticleSystem::~CParticleSystem()
{
	SAFE_DELETE(m_pParticleBuffer);
	SAFE_DELETE(m_pSharedBuffer);
}

void CParticleSystem::finalupdate()
{
	// 추가될 파티클 개수 계산
	m_fAccTime += DT;

	int iAdd = 0;
	if (m_fFrequency < m_fAccTime)
	{
		m_fAccTime = m_fAccTime - m_fFrequency;
		iAdd = 1;
	}

	m_pParticleBuffer->UpdateRWData(6);
	m_pSharedBuffer->UpdateRWData(7);

	m_pUpdateMtrl->SetData(SHADER_PARAM::INT_0, &m_iMaxParticle);
	m_pUpdateMtrl->SetData(SHADER_PARAM::INT_1, &iAdd);
	m_pUpdateMtrl->SetData(SHADER_PARAM::FLOAT_0, &m_fMinLifeTime);
	m_pUpdateMtrl->SetData(SHADER_PARAM::FLOAT_1, &m_fMaxLifeTime);

	m_pUpdateMtrl->SetData(SHADER_PARAM::FLOAT_2, &m_fMinSpeed);
	m_pUpdateMtrl->SetData(SHADER_PARAM::FLOAT_3, &m_fMaxSpeed);

	Vec3 objectUpVector = Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
	Vec4 inputObjectUpVector = Vec4(objectUpVector, 0.f);
	m_pUpdateMtrl->SetData(SHADER_PARAM::VEC4_0, &inputObjectUpVector);

	Vec3 objectRightVector = Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
	Vec4 inputObjectRightVector = Vec4(objectRightVector, 0.f);
	m_pUpdateMtrl->SetData(SHADER_PARAM::VEC4_1, &inputObjectRightVector);

	Vec3 objectFrontVector = Object()->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
	Vec4 inputObjectFrontVector = Vec4(objectFrontVector, 0.f);
	m_pUpdateMtrl->SetData(SHADER_PARAM::VEC4_2, &objectFrontVector);

	m_pUpdateMtrl->ExcuteComputeShader(10, 1, 1);

	m_pParticleBuffer->ClearRWData(6);
	m_pSharedBuffer->ClearRWData(7);
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	m_pParticleBuffer->UpdateData(12);

	m_pMtrl->SetData(SHADER_PARAM::VEC4_0, &m_vStartColor);
	m_pMtrl->SetData(SHADER_PARAM::VEC4_1, &m_vEndColor);
	m_pMtrl->SetData(SHADER_PARAM::FLOAT_0, &m_fStartScale);
	m_pMtrl->SetData(SHADER_PARAM::FLOAT_1, &m_fEndScale);
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, &m_pParticleTexture);

	m_pMtrl->UpdateData();
	m_pMesh->SetLayout(m_pMtrl->GetShader());
	m_pMesh->render_particle(m_iMaxParticle);

	m_pParticleBuffer->ClearData(10);
}

void CParticleSystem::SaveToScene(FILE * _pFile)
{
	//UINT				m_iMaxParticle;    // 최대 파티클 개수
	fwrite(&m_iMaxParticle, sizeof(UINT), 1, _pFile);

	//float				m_fFrequency;		// 파티클 생성 주기
	fwrite(&m_fFrequency, sizeof(float), 1, _pFile);

	//float				m_fMinLifeTime;   // 파티클 최소 생존 시간
	fwrite(&m_fMinLifeTime, sizeof(float), 1, _pFile);
	//float				m_fMaxLifeTime;   // 파티클 최대 생존 시간
	fwrite(&m_fMaxLifeTime, sizeof(float), 1, _pFile);

	//float				m_fMinSpeed;	  // 파티클 시작 속도
	fwrite(&m_fMinSpeed, sizeof(float), 1, _pFile);
	//float				m_fMaxSpeed;	  // 파티클 최종 속도
	fwrite(&m_fMaxSpeed, sizeof(float), 1, _pFile);

	//float				m_fStartScale;   // 파티클 시작 크기
	fwrite(&m_fStartScale, sizeof(float), 1, _pFile);
	//float				m_fEndScale;     // 파티클 최종 크기
	fwrite(&m_fEndScale, sizeof(float), 1, _pFile);

	//Vec4				m_vStartColor;
	fwrite(&m_vStartColor, sizeof(Vec4), 1, _pFile);
	//Vec4				m_vEndColor;
	fwrite(&m_vEndColor, sizeof(Vec4), 1, _pFile);

	//CResPtr<CTexture>	m_pParticleTexture;
	SaveWString(m_pParticleTexture->GetName().c_str(), _pFile);
}

void CParticleSystem::LoadFromScene(FILE * _pFile)
{
	//UINT				m_iMaxParticle;    // 최대 파티클 개수
	fread(&m_iMaxParticle, sizeof(UINT), 1, _pFile);

	//float				m_fFrequency;		// 파티클 생성 주기
	fread(&m_fFrequency, sizeof(float), 1, _pFile);

	//float				m_fMinLifeTime;   // 파티클 최소 생존 시간
	fread(&m_fMinLifeTime, sizeof(float), 1, _pFile);
	//float				m_fMaxLifeTime;   // 파티클 최대 생존 시간
	fread(&m_fMaxLifeTime, sizeof(float), 1, _pFile);

	//float				m_fMinSpeed;	  // 파티클 시작 속도
	fread(&m_fMinSpeed, sizeof(float), 1, _pFile);
	//float				m_fMaxSpeed;	  // 파티클 최종 속도
	fread(&m_fMaxSpeed, sizeof(float), 1, _pFile);

	//float				m_fStartScale;   // 파티클 시작 크기
	fread(&m_fStartScale, sizeof(float), 1, _pFile);
	//float				m_fEndScale;     // 파티클 최종 크기
	fread(&m_fEndScale, sizeof(float), 1, _pFile);

	//Vec4				m_vStartColor;
	fread(&m_vStartColor, sizeof(Vec4), 1, _pFile);
	//Vec4				m_vEndColor;
	fread(&m_vEndColor, sizeof(Vec4), 1, _pFile);

	//CResPtr<CTexture>	m_pParticleTexture;
	wstring strKey = LoadWString(_pFile);
	m_pParticleTexture = CResMgr::GetInst()->FindRes<CTexture>(strKey);
	if (nullptr == m_pParticleTexture)
	{
		CResMgr::GetInst()->Load<CTexture>(strKey, strKey);
	}

	// 구조화 버퍼 생성
	m_pParticleBuffer->Create(sizeof(tParticle), m_iMaxParticle, nullptr);
	m_pSharedBuffer->Create(sizeof(tParticleShared), 1, nullptr);

	// 사각형 Mesh
	m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh");

	// Material
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, &m_pParticleTexture);

	// ParticleUpdate
	m_pUpdateMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleUpdateMtrl");
}