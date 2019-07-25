#pragma once
#include "GameResource.h"

class Mesh : public GameResource
{
private:
	ID3D11Buffer*							m_pVertexBuffer;
	ID3D11Buffer*							m_pIndexBuffer;
	
	UINT									m_uiVertexSize;
	UINT									m_uiVertexCount;
	D3D11_USAGE								m_eVertexUsage;

	UINT									m_uiIndexSize;
	UINT									m_uiIndexCount;

	void*									m_pVertexSysMem;
	void*									m_pIndexSysMem;

	D3D11_PRIMITIVE_TOPOLOGY				m_eTopology;
	std::vector<D3D11_INPUT_ELEMENT_DESC>	m_vecLayout;
	ID3D11InputLayout*						m_pLayout;


public:
	Mesh();
	virtual ~Mesh();

public:
	void CreateMesh(UINT param_uiVertexSize, UINT param_uiVertexCount, D3D11_USAGE param_eVertexUsage, 
		void* param_pVertexSysMem, UINT param_uiIndexSize, UINT param_uiIndexCount, void* param_pIndexSysMem, 
		D3D11_PRIMITIVE_TOPOLOGY param_eTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void SetLayout(ID3DBlob* param_pVertexBlob);
	void Render();

};

