#include "stdafx.h"
#include "Core.h"
#include "Device.h"


Core::Core()
{
}

Core::~Core()
{
	if (m_pVertexBlob != nullptr)
	{
		m_pVertexBlob->Release();
	}

	if (m_pPixelBlob != nullptr)
	{
		m_pPixelBlob->Release();
	}

	if (m_pErrorBlob != nullptr)
	{
		m_pErrorBlob->Release();
	}

	if (m_pVertexShader != nullptr)
	{
		m_pVertexShader->Release();
	}

	if (m_pPixelShader != nullptr)
	{
		m_pPixelShader->Release();
	}

	if (m_pLayout != nullptr)
	{
		m_pLayout->Release();
	}

	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
	}

	if (m_pIndexBuffer != nullptr)
	{
		m_pIndexBuffer->Release();
	}

	if (m_pConstantBuffer != nullptr)
	{
		m_pConstantBuffer->Release();
	}
}

int Core::Init(HWND hWnd, bool bWindowed)
{
	m_hWnd = hWnd;
	m_bWindowed = bWindowed;

	DeviceInit();
	ManagerInit();
	//VertexBufferCreate();
	//IndexBufferCreate();
	ConstantBufferCreate();
	VertexShaderCreate();
	PixelShaderCreate();
	LayoutCreate();
	//ContextInit();


	m_fClearColor[0] = 1.0f;
	m_fClearColor[1] = 1.0f;
	m_fClearColor[2] = 1.0f;
	m_fClearColor[3] = 1.0f;

	m_bFire = false;

	m_iVertexOffset.push_back(0);
	m_iIndexOffset.push_back(0);
	return S_OK;
}

void Core::DeviceInit()
{
	RECT rt;
	GetClientRect(m_hWnd, &rt);

	m_tRes.fWidth = static_cast<float>(rt.right - rt.left);
	m_tRes.fHeight = static_cast<float>(rt.bottom - rt.top);

	bool isSuccess = false;
	if (SUCCEEDED(Device::GetInstance()->Init(m_hWnd, m_tRes, m_bWindowed)))
	{
		isSuccess = true;
	}

	assert(isSuccess);
}

void Core::ManagerInit()
{
	KeyMgr::GetInstance()->Init();
	TimeMgr::GetInstance()->Init();
	FilePathSearch::Init();
}

void Core::VertexBufferCreate()
{
	// Create Vertex Buffer
	std::vector<TVertex> inputVertex;
	m_iVertexOffset.push_back(0);
	{
		TVertex inputData;
		inputData.vPos = DirectX::XMFLOAT3(0.f, 1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(1.f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(-1.f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
		inputVertex.push_back(inputData);
		
		m_iVertexOffset.push_back(inputVertex.size());

		TObjectMatrix inputMatrix;
		inputMatrix.worldPosition = DirectX::XMFLOAT3(0.f, -200.f, 500.f);
		inputMatrix.worldScale = DirectX::XMFLOAT3(30.f, 30.f, 1.f);
		inputMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

		m_tObjectWorldMatrix.push_back(inputMatrix);
	}

	{
		TVertex inputData;
		inputData.vPos = DirectX::XMFLOAT3(-1.f, 1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(1.f, 1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(1.f, -1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(-1.f, -1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		m_iVertexOffset.push_back(inputVertex.size());

		TObjectMatrix inputMatrix;
		inputMatrix.worldPosition = DirectX::XMFLOAT3(0.f, 170.f, 500.f);
		inputMatrix.worldScale = DirectX::XMFLOAT3(30.f, 30.f, 1.f);
		inputMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

		m_tObjectWorldMatrix.push_back(inputMatrix);
	}

	{
		TVertex inputData;
		inputData.vPos = DirectX::XMFLOAT3(0.f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(0.f, 1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(0.6f, 0.6f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(1.f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(0.6f, -0.6f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(0.f, -1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(-0.6f, -0.6f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(-1.0f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(-0.6f, 0.6f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
		inputVertex.push_back(inputData);

		m_iVertexOffset.push_back(inputVertex.size());

		TObjectMatrix inputMatrix;
		inputMatrix.worldPosition = DirectX::XMFLOAT3(0.f, 0.f, 500.f);
		inputMatrix.worldScale = DirectX::XMFLOAT3(5.f, 5.f, 1.f);
		inputMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

		m_tObjectWorldMatrix.push_back(inputMatrix);
	}

	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(TVertex) * inputVertex.size();
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = &inputVertex[0]; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pVertexBuffer);
}

void Core::VertexBufferCreate(std::vector<std::vector<TVertex>> vertexs, std::vector<TObjectMatrix> worldMatrix, std::vector<std::string> name)
{
	// Create Vertex Buffer
	std::vector<TVertex> inputVertex;

	for (int objectIndex = 0; objectIndex < vertexs.size(); objectIndex++)
	{
		inputVertex.insert(inputVertex.end(), vertexs[objectIndex].begin(), vertexs[objectIndex].end());

		m_stdMapObjectName.insert(std::pair<std::string, unsigned int>(name[objectIndex], m_tObjectWorldMatrix.size()));
		m_iVertexOffset.push_back(inputVertex.size());
		m_tObjectWorldMatrix.push_back(worldMatrix[objectIndex]);
	}

	/*{
		TVertex inputData;
		inputData.vPos = DirectX::XMFLOAT3(0.f, 1.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(1.f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		inputData.vPos = DirectX::XMFLOAT3(-1.f, 0.f, 0.5f);
		inputData.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
		inputVertex.push_back(inputData);

		m_iVertexOffset.push_back(inputVertex.size());

		TObjectMatrix inputMatrix;
		inputMatrix.worldPosition = DirectX::XMFLOAT3(0.f, -200.f, 500.f);
		inputMatrix.worldScale = DirectX::XMFLOAT3(30.f, 30.f, 1.f);
		inputMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

		m_tObjectWorldMatrix.push_back(inputMatrix);
	}*/

	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(TVertex) * inputVertex.size();
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = &inputVertex[0]; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pVertexBuffer);

	//UINT iOffset = 0;
	//UINT iStride = sizeof(TVertex);
	//Device::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &iStride, &iOffset);
}

void Core::IndexBufferCreate()
{
	// Create Index Buffer
	std::vector<unsigned int> inputIndex;
	{
		std::vector<unsigned int> inputData = { 
			0, 1, 2 
		};
		inputIndex.insert(inputIndex.end(), inputData.begin(), inputData.end());

		m_iIndexCount.push_back(inputData.size());
		m_iIndexOffset.push_back(inputIndex.size());
	}

	{
		std::vector<unsigned int> inputData = {
			 0, 1, 2,
			 0, 2, 3
		};
		inputIndex.insert(inputIndex.end(), inputData.begin(), inputData.end());

		m_iIndexCount.push_back(inputData.size());
		m_iIndexOffset.push_back(inputIndex.size());
	}

	{
		std::vector<unsigned int> inputData = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 1,
		};
		inputIndex.insert(inputIndex.end(), inputData.begin(), inputData.end());

		m_iIndexCount.push_back(inputData.size());
		m_iIndexOffset.push_back(inputIndex.size());
	}

	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(unsigned int) * inputIndex.size();
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub = {};
	tSub.pSysMem = &inputIndex[0]; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pIndexBuffer);
}

void Core::IndexBufferCreate(std::vector<std::vector<unsigned int>> indexs)
{
	// Create Index Buffer
	std::vector<unsigned int> inputIndex;
	
	for (int objectIndex = 0; objectIndex < indexs.size(); objectIndex++)
	{
		inputIndex.insert(inputIndex.end(), indexs[objectIndex].begin(), indexs[objectIndex].end());

		m_iIndexCount.push_back(indexs[objectIndex].size());
		m_iIndexOffset.push_back(inputIndex.size());
	}
	/*{
		std::vector<unsigned int> inputData = {
			0, 1, 2
		};
		inputIndex.insert(inputIndex.end(), inputData.begin(), inputData.end());

		m_iIndexCount.push_back(inputData.size());
		m_iIndexOffset.push_back(inputIndex.size());
	}

	{
		std::vector<unsigned int> inputData = {
			0, 1, 2,
			0, 2, 3
		};
		inputIndex.insert(inputIndex.end(), inputData.begin(), inputData.end());

		m_iIndexCount.push_back(inputData.size());
		m_iIndexOffset.push_back(inputIndex.size());
	}

	{
		std::vector<unsigned int> inputData = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 1,
		};
		inputIndex.insert(inputIndex.end(), inputData.begin(), inputData.end());

		m_iIndexCount.push_back(inputData.size());
		m_iIndexOffset.push_back(inputIndex.size());
	}*/

	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(unsigned int) * inputIndex.size();
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub = {};
	tSub.pSysMem = &inputIndex[0]; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &m_pIndexBuffer);

	//Device::GetInstance()->GetContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Core::ConstantBufferCreate()
{
	//Create Constant Buffer
	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX) * 3;
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, nullptr, &m_pConstantBuffer);
}

void Core::VertexShaderCreate()
{
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif
	std::wstring strPath = FilePathSearch::GetPath();
	strPath += L"Engine\\VertexShader.hlsl";

	HRESULT result = D3DCompileFromFile(
		strPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		iFlag,
		0,
		&m_pVertexBlob,
		&m_pErrorBlob
	);

	Device::GetInstance()->GetDevice()->CreateVertexShader(
		m_pVertexBlob->GetBufferPointer(),
		m_pVertexBlob->GetBufferSize(),
		nullptr,
		&m_pVertexShader
	);
}

void Core::PixelShaderCreate()
{
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif
	std::wstring strPath = FilePathSearch::GetPath();
	strPath += L"Engine\\PixelShader.hlsl";

	HRESULT result = D3DCompileFromFile(
		strPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		iFlag,
		0,
		&m_pPixelBlob,
		&m_pErrorBlob
	);

	Device::GetInstance()->GetDevice()->CreatePixelShader(
		m_pPixelBlob->GetBufferPointer(),
		m_pPixelBlob->GetBufferSize(),
		nullptr,
		&m_pPixelShader
	);
}

void Core::LayoutCreate()
{
	HRESULT result;
	UINT iByteOffset = 0;

	std::vector<D3D11_INPUT_ELEMENT_DESC> vecLayout;

	D3D11_INPUT_ELEMENT_DESC tLayoutDesc = {};

	tLayoutDesc.AlignedByteOffset = iByteOffset;
	tLayoutDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tLayoutDesc.InputSlot = 0;
	tLayoutDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc.InstanceDataStepRate = 0;
	tLayoutDesc.SemanticName = "POSITION";
	tLayoutDesc.SemanticIndex = 0;

	vecLayout.push_back(tLayoutDesc);

	iByteOffset += sizeof(DirectX::XMFLOAT3);

	tLayoutDesc.AlignedByteOffset = iByteOffset;
	tLayoutDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tLayoutDesc.InputSlot = 0;
	tLayoutDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc.InstanceDataStepRate = 0;
	tLayoutDesc.SemanticName = "COLOR";
	tLayoutDesc.SemanticIndex = 0;

	vecLayout.push_back(tLayoutDesc);

	iByteOffset += sizeof(DirectX::XMFLOAT4);

	result = Device::GetInstance()->GetDevice()->CreateInputLayout(
		&vecLayout[0],
		vecLayout.size(),
		m_pVertexBlob->GetBufferPointer(),
		m_pVertexBlob->GetBufferSize(),
		&m_pLayout
	);
}

void Core::ContextInit()
{
	UINT iOffset = 0;
	UINT iStride = sizeof(TVertex);

	Device::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &iStride, &iOffset);
	Device::GetInstance()->GetContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	Device::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device::GetInstance()->GetContext()->IASetInputLayout(m_pLayout);

	Device::GetInstance()->GetContext()->VSSetShader(m_pVertexShader, nullptr, 0);
	Device::GetInstance()->GetContext()->PSSetShader(m_pPixelShader, nullptr, 0);
}

void Core::Update()
{
	KeyMgr::GetInstance()->Update();
	TimeMgr::GetInstance()->Update();
}

void Core::Render()
{
	Device::GetInstance()->Clear(m_fClearColor);

	UINT iOffset = 0;
	UINT iStride = sizeof(TVertex);

	Device::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &iStride, &iOffset);
	Device::GetInstance()->GetContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	Device::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device::GetInstance()->GetContext()->IASetInputLayout(m_pLayout);

	Device::GetInstance()->GetContext()->VSSetShader(m_pVertexShader, nullptr, 0);
	Device::GetInstance()->GetContext()->PSSetShader(m_pPixelShader, nullptr, 0);

	for (unsigned int index = 0; index < m_iIndexCount.size(); index++)
	{
		ApplyMatrix(m_tObjectWorldMatrix[index].worldPosition, m_tObjectWorldMatrix[index].worldScale, m_tObjectWorldMatrix[index].worldRotation);
		Device::GetInstance()->GetContext()->DrawIndexed(m_iIndexCount[index], m_iIndexOffset[index], m_iVertexOffset[index]);
	}

	Device::GetInstance()->Present();
}

void Core::ApplyMatrix(DirectX::XMFLOAT3 worldPosition, DirectX::XMFLOAT3 worldScale, DirectX::XMFLOAT3 worldRotation)
{
	DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z);
	DirectX::XMMATRIX matRotationX = DirectX::XMMatrixRotationX(worldRotation.x);
	DirectX::XMMATRIX matRotationY = DirectX::XMMatrixRotationY(worldRotation.y);
	DirectX::XMMATRIX matRotationZ = DirectX::XMMatrixRotationZ(worldRotation.z);
	DirectX::XMMATRIX matTrans = DirectX::XMMatrixTranslation(worldPosition.x, worldPosition.y, worldPosition.z);

	DirectX::XMMATRIX matWorld = matScale * matRotationX * matRotationY * matRotationZ * matTrans;

	matWorld = DirectX::XMMatrixTranspose(matWorld);

	//View 행렬 만들기
	DirectX::XMMATRIX matView = DirectX::XMMatrixIdentity();

	matView = DirectX::XMMatrixTranspose(matView);

	//Projection 행렬 만들기
	DirectX::XMMATRIX matProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), m_tRes.fWidth / m_tRes.fHeight, 1.f, 1000.f);

	matProjection = DirectX::XMMatrixTranspose(matProjection);

	D3D11_MAPPED_SUBRESOURCE tSub = {};

	Device::GetInstance()->GetContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	DirectX::XMMATRIX arrMatrix[3] = { matWorld, matView, matProjection };
	memcpy(tSub.pData, &arrMatrix, sizeof(DirectX::XMMATRIX) * 3);
	Device::GetInstance()->GetContext()->Unmap(m_pConstantBuffer, 0);

	Device::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

void Core::SetObjectWorldPositionMatrix(std::string name, DirectX::XMFLOAT3 worldPosition)
{
	if (m_stdMapObjectName.find(name) != m_stdMapObjectName.end())
	{
		unsigned int matrixIndex = m_stdMapObjectName[name];
		m_tObjectWorldMatrix[matrixIndex].worldPosition = worldPosition;
	}
}

void Core::SetObjectWorldScaleMatrix(DirectX::XMFLOAT3 worldScale)
{
}

void Core::SetObjectWorldRotationMatrix(DirectX::XMFLOAT3 worldRotation)
{
}

