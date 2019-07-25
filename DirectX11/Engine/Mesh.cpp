#include "stdafx.h"
#include "Mesh.h"
#include "Device.h"

Mesh::Mesh()
	: m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
{
}


Mesh::~Mesh()
{
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();

	delete m_pVertexSysMem;
	delete m_pIndexSysMem;

	m_pLayout->Release();
}

void Mesh::CreateMesh(
	UINT param_uiVertexSize, UINT param_uiVertexCount, D3D11_USAGE param_eVertexUsage, void * param_pVertexSysMem, 
	UINT param_uiIndexSize, UINT param_uiIndexCount, void * param_pIndexSysMem, 
	D3D11_PRIMITIVE_TOPOLOGY param_eTopology)
{
	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = param_uiVertexSize * param_uiVertexCount;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = param_eVertexUsage;

	if (param_eVertexUsage == D3D11_USAGE_DYNAMIC)
	{
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = param_pVertexSysMem; 

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pVertexBuffer);

	tBufferDesc.ByteWidth = param_uiIndexSize * param_uiIndexCount;
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.CPUAccessFlags = 0;

	tSub = {};
	tSub.pSysMem = param_pIndexSysMem; 

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pIndexBuffer);

	m_uiVertexCount = param_uiVertexCount;
	m_uiVertexSize = param_uiVertexSize;
	m_uiIndexCount = param_uiIndexCount;
	m_uiIndexSize = param_uiIndexSize;
	m_eTopology = param_eTopology;

	m_pVertexSysMem = malloc(m_uiVertexCount * m_uiVertexSize);
	m_pIndexSysMem = malloc(m_uiIndexCount * m_uiIndexSize);

	memcpy(m_pVertexSysMem, param_pVertexSysMem, m_uiVertexCount * m_uiVertexSize);
	memcpy(m_pIndexSysMem, param_pIndexSysMem, m_uiIndexCount * m_uiIndexSize);


	UINT iByteOffset = 0;
	D3D11_INPUT_ELEMENT_DESC tLayoutDesc = {};

	tLayoutDesc.AlignedByteOffset = iByteOffset;
	tLayoutDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tLayoutDesc.InputSlot = 0;
	tLayoutDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc.InstanceDataStepRate = 0;
	tLayoutDesc.SemanticName = "POSITION";
	tLayoutDesc.SemanticIndex = 0;

	m_vecLayout.push_back(tLayoutDesc);

	iByteOffset += sizeof(DirectX::XMFLOAT3);

	tLayoutDesc.AlignedByteOffset = iByteOffset;
	tLayoutDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tLayoutDesc.InputSlot = 0;
	tLayoutDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc.InstanceDataStepRate = 0;
	tLayoutDesc.SemanticName = "COLOR";
	tLayoutDesc.SemanticIndex = 0;

	m_vecLayout.push_back(tLayoutDesc);

	iByteOffset += sizeof(DirectX::XMFLOAT4);

}

void Mesh::SetLayout(ID3DBlob * param_pVertexBlob)
{
	if (nullptr != m_pLayout)
	{
		m_pLayout->Release();
		m_pLayout = nullptr;
	}

	 Device::GetInstance()->GetDevice()->CreateInputLayout(
		 &m_vecLayout[0],
		 m_vecLayout.size(),
		 param_pVertexBlob->GetBufferPointer(),
		 param_pVertexBlob->GetBufferSize(),
		 &m_pLayout);
}

void Mesh::Render()
{
	UINT iStride = m_uiVertexSize;
	UINT iOffset = 0;

	Device::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &iStride, &iOffset);
	Device::GetInstance()->GetContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	Device::GetInstance()->GetContext()->IASetPrimitiveTopology(m_eTopology);
	Device::GetInstance()->GetContext()->IASetInputLayout(m_pLayout);

	Device::GetInstance()->GetContext()->DrawIndexed(m_uiIndexCount, 0, 0);

}
