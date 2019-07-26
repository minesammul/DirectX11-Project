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

	UINT		m_uiLayerCheck;

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

	PROJ_TYPE GetProjType() { return m_eType; }
	float GetScale() { return m_fScale; }
	float GetNear() { return m_fNear; }
	float GetFar() { return m_fFar; }
	float GetFOV() { return m_fFOV; }

	const DirectX::XMMATRIX& GetViewMat() { return m_matView; }
	const DirectX::XMMATRIX& GetProjMat() { return m_matProj; }

	void CheckLayer(UINT _iLayerIdx);
	bool IsValiedLayer(UINT _iLayerIdx) { return m_uiLayerCheck & (1 << _iLayerIdx); }
};

