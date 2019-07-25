#pragma once
#include "Component.h"

enum class PROJ_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};

class Camera : public Component
{
private:
	DirectX::XMMATRIX		m_matView;
	DirectX::XMMATRIX		m_matProj;

	PROJ_TYPE	m_eType;
	float		m_fScale; // 직교투영 배율
	float		m_fFOV;	  // 시야각

	float		m_fNear;
	float		m_fFar;

public:
	Camera();
	virtual ~Camera();

public:
	virtual void Update();
	void FinalUpdate();

public:
	void SetProjType(PROJ_TYPE _eType) { m_eType = _eType; }
	void SetScale(float _f) { m_fScale = _f; }
	void SetNear(float _N) { m_fNear = _N; }
	void SetFar(float _F) { m_fFar = _F; }
	void SetFOV(float _FOV) { m_fFOV = _FOV; }

	PROJ_TYPE GetProjType(PROJ_TYPE _eType) { m_eType = _eType; }
	float GetScale(float _f) { return m_fScale; }
	float GetNear(float _N) { return m_fNear; }
	float GetFar(float _F) { return m_fFar; }
	float GetFOV(float _FOV) { return m_fFOV; }


};

