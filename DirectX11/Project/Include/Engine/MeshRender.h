#pragma once

#include "Component.h"


#include "ResPtr.h"

#include "Mesh.h"
#include "Material.h"

class CMeshRender :
	public CComponent
{
private:
	CResPtr<CMesh>		m_pMesh;
	vector<CResPtr<CMaterial>>  m_vecMtrl;

public:
	void SetMesh(CResPtr<CMesh>	_pMesh);
	void SetMaterial(CResPtr<CMaterial> _pMtrl, UINT _iSubset = 0) { m_vecMtrl[_iSubset] = _pMtrl; }

	CResPtr<CMesh> GetMesh() { return m_pMesh; }
	CResPtr<CMaterial> GetCloneMaterial(UINT _iSubset = 0); // 20200102 변경
	CResPtr<CMaterial> GetSharedMaterial(UINT _iSubset = 0) { return m_vecMtrl[_iSubset]; } // 20200102 변경
	UINT GetMaterialCount() { return m_vecMtrl.size(); }

public:
	virtual void update();
	void render();

	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	CLONE(CMeshRender);

public:
	CMeshRender();
	virtual ~CMeshRender();
};

