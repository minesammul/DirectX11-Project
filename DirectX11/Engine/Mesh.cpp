#include "stdafx.h"
#include "Mesh.h"
#include "Device.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

Mesh * Mesh::CreateMesh(UINT uiVertexSize, UINT uiVertexCount, D3D11_USAGE eVertexUsage, void* pVertexSysMem, UINT uiIndexSize, UINT uiIndexCount, void* pIndexSysMem)
{
	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = uiVertexSize * uiVertexCount;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = eVertexUsage;

	if (eVertexUsage == D3D11_USAGE_DYNAMIC)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = pVertexSysMem; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pVertexBuffer);

	tBufferDesc.ByteWidth = uiIndexSize * uiIndexCount;
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.CPUAccessFlags = 0;

	tSub = {};
	tSub.pSysMem = pIndexSysMem; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pIndexBuffer);

	m_uiVertexCount = uiVertexCount;
	m_uiVertexSize = uiVertexSize;
	m_uiIndexCount = uiIndexCount;
	m_uiIndexSize = uiIndexSize;

	m_pVertexSysMem = malloc(m_uiVertexCount * m_uiVertexSize);
	m_pIndexSysMem = malloc(m_uiIndexCount * m_uiIndexSize);

	memcpy(m_pVertexSysMem, pVertexSysMem, m_uiVertexCount * m_uiVertexSize);
	memcpy(m_pIndexSysMem, pIndexSysMem, m_uiIndexCount * m_uiIndexSize);

	return nullptr;
}
