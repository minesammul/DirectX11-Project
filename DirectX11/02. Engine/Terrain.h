#pragma once
#include "Component.h"

class CTerrain :
	public CComponent
{
private:
	UINT		m_iXFaceCount;
	UINT		m_iZFaceCount;

public:
	void init(UINT _iXFace, UINT _iZFace);

private:
	void SetFaceCount(UINT _iXFace, UINT _iZFace);


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

