#pragma once
#include <Engine/Script.h>


class CToolCamScript :
	public CScript
{
private:
	float		m_fSpeed;
	float		m_fMul;
	
	bool m_isNavMeshCreate;
	CGameObject* m_selectNavMesh;
	bool m_isNavMeshModify;

private:
	CGameObject* GetClickNavMesh();
	void RotateAxisRadian(CGameObject* rotateMesh, Vec3 rotateAxis, float rotateAngle, Vec3 & inOutScale, Vec3 & inOutRotate, Vec3 &inOutPosition);

public:
	virtual void start();
	virtual void update();

public:
	CLONE(CToolCamScript)

public:
	CToolCamScript();
	virtual ~CToolCamScript();
};

