#pragma once

#include "Resource.h"
#include "FBXLoader.h"

#include "ResPtr.h"

#include "Resource.h"
#include "Material.h"
#include "Mesh.h"

class CGameObject;


class CMeshData :
	public CResource
{
private:
	vector<CResPtr<CMesh>>				m_vecMesh;
	vector<vector<CResPtr<CMaterial>>>	m_vecMtrl;
	
	// Animation3D
public:
	static CMeshData* LoadFromFBX(const wstring& _strFilePath);
	
	virtual void Load(const wstring& _strFilePath);
	virtual void Save();

	virtual bool LoadFromScene(FILE* _pFile);

	CGameObject* Instantiate();	
	vector<CResPtr<CMesh>> GetVectorMesh();
	void SetVectorMesh(CResPtr<CMesh> mesh, int index);

	CLONE_DISABLE(CMeshData);
public:
	CMeshData();
	virtual ~CMeshData();
};