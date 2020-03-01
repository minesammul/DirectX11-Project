#pragma once
#include "Component.h"

#include "ResPtr.h"
#include "Texture.h"
#include "Material.h"

enum class TERRAIN_MOD
{
	HEIGHTMAP,
	SPLATTING,
	END,
};

class CTerrain :
	public CComponent
{
private:
	UINT				m_iXFaceCount;
	UINT				m_iZFaceCount;
	TERRAIN_MOD			m_eMod;
	Vec2				m_vBrushScale;

	CResPtr<CTexture>	m_pHeightMap;
	CResPtr<CMaterial>  m_pHeightMapMtrl;

	CResPtr<CTexture>	m_pWeightTex;
	CResPtr<CMaterial>  m_pWeightMtrl;
	int					m_iTileIdx;

	vector<CResPtr<CTexture>> m_vecBrush;
	UINT						m_iBrushIdx;

	CResPtr<CTexture>	m_pOutput;
	CResPtr<CMaterial>  m_pPickMtrl;
	CCamera*			m_pToolCam;

	//CResPtr<CTexture>	m_pHeightValueOutput;
	//CResPtr<CMaterial>  m_pHeightValueMtrl;

	int heightMapPlusIsUpMiusIsDown;
public:
	void init(UINT _iXFace, UINT _iZFace);

private:
	void ModCheck();
	void KeyCheck();
	int Picking(Vec2& _vPos);

	void SetMaterialParameter();
	
	void LoadResource();

public:
	virtual void update() {};
	virtual void finalupdate();

public:
	void SetCamera(CCamera* _pCam) { m_pToolCam = _pCam; }

public:
	CLONE(CTerrain);
	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

public:
	CTerrain();
	virtual ~CTerrain();
};

