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
	CStructuredBuffer*	m_pParticleBuffer; // ��ƼŬ ������ ����
	CStructuredBuffer*	m_pSharedBuffer;   // ��ƼŬ ���� �޸�
	UINT				m_iMaxParticle;    // �ִ� ��ƼŬ ����

	CResPtr<CMaterial>	m_pUpdateMtrl;		// ��ǻƮ ���̴�
	CResPtr<CMaterial>	m_pMtrl;			// ��ƼŬ ��������
	CResPtr<CMesh>		m_pMesh;			// ��� �޽�(Point Mesh �⺻)

	float				m_fFrequency;		// ��ƼŬ ���� �ֱ�
	float				m_fAccTime;		   // �����ð� üũ�뵵

	float				m_fMinLifeTime;   // ��ƼŬ �ּ� ���� �ð�
	float				m_fMaxLifeTime;   // ��ƼŬ �ִ� ���� �ð�

	float				m_fMinSpeed;	  // ��ƼŬ ���� �ӵ�
	float				m_fMaxSpeed;	  // ��ƼŬ ���� �ӵ�

	float				m_fStartScale;   // ��ƼŬ ���� ũ��
	float				m_fEndScale;     // ��ƼŬ ���� ũ��

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

