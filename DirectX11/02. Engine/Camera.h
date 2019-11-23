#pragma once
#include "Component.h"

enum class PROJ_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};

class CCamera :
	public CComponent
{
protected:
	Matrix		m_matView;
	Matrix		m_matProj;

	PROJ_TYPE	m_eType;
	float		m_fScale; // �������� ����
	float		m_fFOV;	  // �þ߰�

	float		m_fNear;
	float		m_fFar;

	UINT		m_iLayerCheck;
	UINT		m_iCamOrder;

public:
	virtual void update();
	void finalupdate();
	void render();

public:
	void SetProjType(PROJ_TYPE _eType) { m_eType = _eType; }

	void SetScale(float _f) 
	{ 
		if (_f == 0.f)
		{
			m_fScale = 0.01f;
		}
		else
		{
			m_fScale = _f;
		}
	}
	
	void SetNear(float _N) { m_fNear = _N; }
	void SetFar(float _F) { m_fFar = _F; }
	void SetFOV(float _FOV) { if (_FOV == 0.f) m_fFOV = 0.01f; else m_fFOV = _FOV; }
	void SetCamOrder(UINT _iCamOrder) { m_iCamOrder = _iCamOrder; }

	PROJ_TYPE GetProjType() { return m_eType; }
	float GetScale() { return m_fScale; }
	float GetNear() { return m_fNear; }
	float GetFar() { return m_fFar; }
	float GetFOV() { return m_fFOV; }
	UINT GetCamOrder() { return m_iCamOrder; }

	const Matrix& GetViewMat() { return m_matView; }
	const Matrix& GetProjMat() { return m_matProj; }

	void CheckLayer(UINT _iLayerIdx);
	bool IsValiedLayer(UINT _iLayerIdx){return m_iLayerCheck & (1 << _iLayerIdx);}

	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	CLONE(CCamera);

public:
	CCamera();
	virtual ~CCamera();
};

