#include "stdafx.h"
#include "Core.h"
#include "Device.h"
#include "FilePathSearch.h"
#include "KeyMgr.h"
#include "TimeMgr.h"



TVertex g_arrVtx[4] = {};

ID3D11Buffer * g_pVB = nullptr;
ID3D11Buffer * g_pIB = nullptr;
ID3D11Buffer* g_pCB = nullptr;

ID3DBlob*	   g_pVtxBlob = nullptr;
ID3DBlob*	   g_pPixelBlob = nullptr;
ID3DBlob*	   g_pErrorBlob = nullptr;

ID3D11VertexShader * g_pVtxShader = nullptr;
ID3D11PixelShader * g_pPixelShader = nullptr;

ID3D11InputLayout* g_pLayout = nullptr;

DirectX::XMFLOAT3 g_vWorldPos = DirectX::XMFLOAT3(10.f, 0.f, 10.f);
DirectX::XMFLOAT3 g_vWorldScale = DirectX::XMFLOAT3(1.f, 1.f, 1.f);
DirectX::XMFLOAT3 g_vWorldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);


Core::Core()
{
}


Core::~Core()
{
	g_pVtxBlob->Release();
	g_pPixelBlob->Release();

	if (g_pErrorBlob != nullptr)
	{
		g_pErrorBlob->Release();
	}

	g_pVtxShader->Release();
	g_pPixelShader->Release();
	g_pLayout->Release();

	g_pVB->Release();
	g_pCB->Release();
}

int Core::Init(HWND hWnd, bool bWindowed)
{
	m_hWnd = hWnd;

	RECT rt;
	GetClientRect(m_hWnd, &rt);

	m_tRes.fWidth = static_cast<float>(rt.right - rt.left);
	m_tRes.fHeight = static_cast<float>(rt.bottom - rt.top);
	
	if (FAILED(Device::GetInstance()->Init(hWnd, m_tRes, bWindowed)))
	{
		return E_FAIL;
	}

	KeyMgr::GetInstance()->Init();
	TimeMgr::GetInstance()->Init();
	FilePathSearch::Init();

	// Create Vertex Buffer
	g_arrVtx[0].vPos = DirectX::XMFLOAT3(-0.5f, 0.5f, 0.4f);
	g_arrVtx[0].vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = DirectX::XMFLOAT3(0.5f, 0.5f, 0.4f);
	g_arrVtx[1].vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = DirectX::XMFLOAT3(-0.5f, -0.5f, 0.4f);
	g_arrVtx[2].vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = DirectX::XMFLOAT3(0.5f, -0.5f, 0.4f);
	g_arrVtx[3].vColor = DirectX::XMFLOAT4(0.5f, 0.5f, 0.f, 1.f);

	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = sizeof(TVertex) * 4;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_arrVtx; // Àü¿ªº¯¼ö¿¡ ÀúÀåÇØµÐ Á¤Á¡ Á¤º¸¸¦ GPU ¸Þ¸ð¸® ÃÊ±â°ªÀ¸·Î Àü´Þ

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &g_pVB);

	// Create Index Buffer
	WORD arrIdx[6] = { 0, 3, 2, 0, 1, 3 };

	tBufferDesc.ByteWidth = sizeof(WORD) * 6;
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.CPUAccessFlags = 0;

	tSub = {};
	tSub.pSysMem = arrIdx; // Àü¿ªº¯¼ö¿¡ ÀúÀåÇØµÐ Á¤Á¡ Á¤º¸¸¦ GPU ¸Þ¸ð¸® ÃÊ±â°ªÀ¸·Î Àü´Þ

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &g_pIB);

	//Create Constant Buffer
	tBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX) * 3;
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, nullptr, &g_pCB);


	// Shader ¸¸µé±â
	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif
	std::wstring strPath = FilePathSearch::GetPath();
	strPath += L"Engine\\VertexShader.hlsl";
	
	// VtxShader Compile
	/*D3DCompileFromFile(
		strPath.c_str(), 
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		"VS", 
		"vs_5_0", 
		iFlag, 
		0, 
		&g_pVtxBlob, 
		&g_pErrorBlob
	);*/
	HRESULT result =  D3DCompileFromFile(
		strPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		iFlag,
		0,
		&g_pVtxBlob,
		&g_pErrorBlob
	);

	Device::GetInstance()->GetDevice()->CreateVertexShader(
		g_pVtxBlob->GetBufferPointer(), 
		g_pVtxBlob->GetBufferSize(), 
		nullptr, 
		&g_pVtxShader
	);

	//Pixel Shader Create
	strPath = FilePathSearch::GetPath();
	strPath += L"Engine\\PixelShader.hlsl";
	result = D3DCompileFromFile(
		strPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		iFlag,
		0,
		&g_pPixelBlob,
		&g_pErrorBlob
	);

	Device::GetInstance()->GetDevice()->CreatePixelShader(
		g_pPixelBlob->GetBufferPointer(),
		g_pPixelBlob->GetBufferSize(),
		nullptr,
		&g_pPixelShader
	);
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
		g_pVtxBlob->GetBufferPointer(), 
		g_pVtxBlob->GetBufferSize(), 
		&g_pLayout
	);

	return S_OK;
}

void Core::Progress()
{
	Update();
	Render();
}

void Core::Update()
{
	KeyMgr::GetInstance()->Update();
	TimeMgr::GetInstance()->Update();

	if (KEYHOLD(KEY_TYPE::KEY_LEFT))
	{
		g_vWorldPos.x -= 100.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_RIGHT))
	{
		g_vWorldPos.x += 100.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_UP))
	{
		g_vWorldPos.y += 100.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_DOWN))
	{
		g_vWorldPos.y -= 100.f * DT;
	}
	DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(g_vWorldScale.x, g_vWorldScale.y, g_vWorldScale.z);
	DirectX::XMMATRIX matRotationX = DirectX::XMMatrixRotationX(g_vWorldRotation.x);
	DirectX::XMMATRIX matRotationY = DirectX::XMMatrixRotationY(g_vWorldRotation.y);
	DirectX::XMMATRIX matRotationZ = DirectX::XMMatrixRotationZ(g_vWorldRotation.z);
	DirectX::XMMATRIX matTrans = DirectX::XMMatrixTranslation(g_vWorldPos.x, g_vWorldPos.y, g_vWorldPos.z);

	DirectX::XMMATRIX matWorld = matScale * matRotationX * matRotationY * matRotationZ * matTrans;


	D3D11_MAPPED_SUBRESOURCE tSub = {};

	Device::GetInstance()->GetContext()->Map(g_pCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &matWorld, sizeof(DirectX::XMMATRIX));
	Device::GetInstance()->GetContext()->Unmap(g_pCB, 0);

	// ï¿½ï¿½ï¿?0ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Þ¸ð¸®¿ï¿½ Vertex Shader ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ø´ï¿½ ï¿½ï¿½ï¿½Û¸ï¿½ ï¿½ï¿½ï¿½ï¿½
	Device::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, &g_pCB);
}

void Core::Render()
{
	float color[4] = {
		0.f,
		1.f,
		1.f,
		1.f
	};

	Device::GetInstance()->Clear(color);

	UINT iOffset = 0;
	UINT iStride = sizeof(TVertex);

	Device::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &g_pVB, &iStride, &iOffset);
	Device::GetInstance()->GetContext()->IASetIndexBuffer(g_pIB, DXGI_FORMAT_R16_UINT, 0);
	Device::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device::GetInstance()->GetContext()->IASetInputLayout(g_pLayout);

	Device::GetInstance()->GetContext()->VSSetShader(g_pVtxShader, nullptr, 0);
	Device::GetInstance()->GetContext()->PSSetShader(g_pPixelShader, nullptr, 0);
	Device::GetInstance()->GetContext()->DrawIndexed(6, 0, 0);

	Device::GetInstance()->Present();

}
