#pragma once
#include "Component.h"
#include "ResPtr.h"
#include "Material.h"
#include "Mesh.h"

class CStructuredBuffer;

class CParticleSystem :
	public CComponent
{
private:
	CStructuredBuffer*	m_pParticleBuffer; // 파티클 데이터 저장
	CStructuredBuffer*	m_pSharedBuffer;   // 파티클 공유 메모리
	UINT				m_iMaxParticle;    // 최대 파티클 개수

	CResPtr<CMaterial>	m_pUpdateMtrl;		// 컴퓨트 쉐이더
	CResPtr<CMaterial>	m_pMtrl;			// 파티클 렌더링용
	CResPtr<CMesh>		m_pMesh;			// 사용 메쉬(Point Mesh 기본)

	float				m_fFrequency;		// 파티클 생성 주기
	float				m_fAccTime;		   // 누적시간 체크용도

	float				m_fMinLifeTime;   // 파티클 최소 생존 시간
	float				m_fMaxLifeTime;   // 파티클 최대 생존 시간

	float				m_fMinSpeed;	  // 파티클 시작 속도
	float				m_fMaxSpeed;	  // 파티클 최종 속도

	float				m_fStartScale;   // 파티클 시작 크기
	float				m_fEndScale;     // 파티클 최종 크기

	Vec4				m_vStartColor;
	Vec4				m_vEndColor;

	CResPtr<CTexture>	m_pParticleTexture;

public:
	virtual void update() {}
	virtual void finalupdate();
	virtual void render();

public:
	void SetStartColor(Vec4 _vColor) { m_vStartColor = _vColor; }
	Vec4 GetStartColor() { return m_vStartColor; }

	void SetEndColor(Vec4 _vColor) { m_vEndColor = _vColor; }
	Vec4 GetEndColor() { return m_vEndColor; }

	void SetParticleTexture(CResPtr<CTexture> texture) 	{ m_pParticleTexture = texture; }
	wstring GetParticleTextureName() { return m_pParticleTexture->GetName(); }

	void SetStartScale(float scale) { m_fStartScale = scale; }
	float GetStartScale() { return m_fStartScale; }

	void SetEndScale(float scale) { m_fEndScale = scale; }
	float GetEndScale() { return m_fEndScale; }

	void SetMinSpeed(float speed) { m_fMinSpeed = speed; }
	float GetMinSpeed() { return m_fMinSpeed; }

	void SetMaxSpeed(float speed) { m_fMaxSpeed = speed; }
	float GetMaxSpeed() { return m_fMaxSpeed; }

	void SetMaxParticleCount(UINT count) { m_iMaxParticle = count; }
	UINT GetMaxParticleCount() { return m_iMaxParticle; }

	void SetFrequency(float frequency) { m_fFrequency = frequency; }
	float GetFrequency() { return m_fFrequency; }

	void SetMinLifeTime(float lifeTime) { m_fMinLifeTime = lifeTime; }
	float GetMinLifeTime() { return m_fMinLifeTime; }

	void SetMaxLifeTime(float lifeTime) { m_fMaxLifeTime = lifeTime; }
	float GetMaxLifeTime() { return m_fMaxLifeTime; }

public:
	CLONE(CParticleSystem);
	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

public:
	CParticleSystem();
	virtual ~CParticleSystem();
};

