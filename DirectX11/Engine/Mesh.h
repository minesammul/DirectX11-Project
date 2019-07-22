#pragma once
#include "Resource.h"
class Mesh : public Resource
{
private:
	ID3D11Buffer*	m_pVertexBuffer;
	ID3D11Buffer*	m_pIndexBuffer;

	UINT			m_uiVertexSize;
	UINT			m_uiVertexCount;
	D3D11_USAGE		m_eVertexUsage;

	UINT			m_uiIndexSize;
	UINT			m_uiIndexCount;

	void*			m_pVertexSysMem;
	void*			m_pIndexSysMem;

public:
	Mesh();
	virtual ~Mesh();

public:
	Mesh * CreateMesh(UINT uiVertexSize, UINT uiVertexCount, D3D11_USAGE eVertexUsage, void* pVertexSysMem, UINT uiIndexSize, UINT uiIndexCount, void* pIndexSysMem);

};

