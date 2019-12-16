#pragma once
#include "Component.h"

#include "ResPtr.h"
#include "Texture.h"
#include "Material.h"

class CTerrain :
	public CComponent
{
private:
	UINT				m_iXFaceCount;
	UINT				m_iZFaceCount;
	CResPtr<CTexture>	m_pHeightMap;
	CResPtr<CMaterial>  m_pHeightMapMtrl;
	vector<CResPtr<CTexture>> m_vecBrush;

public:
	void init(UINT _iXFace, UINT _iZFace);

private:
	void SetFaceCount(UINT _iXFace, UINT _iZFace);
	void CreateComputeShader();
	void LoadResource();

public:
	virtual void update() {};
	virtual void finalupdate();

public:
	CLONE(CTerrain);
	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

public:
	CTerrain();
	virtual ~CTerrain();
};

