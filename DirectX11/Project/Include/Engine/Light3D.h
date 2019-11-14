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
	void SetLightDiffuse(const Vec3& _vLightColor) { m_tInfo.vDiff = _vLightColor; }
	void SetLightSpecular(const Vec3& _vLightSpec) { m_tInfo.vSpec = _vLightSpec; }
	void SetLightAmbient(const Vec3& _vLightAmb) { m_tInfo.vAmb = _vLightAmb; }
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

