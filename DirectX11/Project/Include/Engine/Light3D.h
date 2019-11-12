#pragma once
#include "Component.h"

class CLight3D :
	public CComponent
{
private:
	tLight3DInfo		m_tInfo;


public:
	virtual void update() {}
	virtual void finalupdate();

public:
	void SetLightType(LIGHT_TYPE _eType);
	void SetLightDir(const Vec3& _vLightDir) { m_tInfo.vDir = _vLightDir; m_tInfo.vDir.Normalize(); }
	void SetLightColor(const Vec3& _vLightColor) {m_tInfo.vColor = _vLightColor;}
	void SetLightRange(float _fRange) {m_tInfo.fRange = _fRange;}
	void SetLightAngle(float _fAngle) { m_tInfo.fAngle = _fAngle; }


	virtual void SaveToScene(FILE* _pFile) {};
	virtual void LoadFromScene(FILE* _pFile) {};

	const tLight3DInfo& GetLight3DInfo() { return m_tInfo; }


public:
	CLONE(CLight3D);

public:
	CLight3D();
	virtual ~CLight3D();
};

