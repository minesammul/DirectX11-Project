#include "stdafx.h"
#include "Core.h"
#include "Device.h"
#include "FilePathSearch.h"

TVertex g_arrVtx[3] = {};

ID3D11Buffer * g_pVB = nullptr;
//ID3D11Buffer * g_pIB = nullptr;

ID3DBlob*	   g_pVtxBlob = nullptr;
ID3DBlob*	   g_pPixelBlob = nullptr;
ID3DBlob*	   g_pErrorBlob = nullptr;

ID3D11VertexShader * g_pVtxShader = nullptr;
ID3D11PixelShader * g_pPixelShader = nullptr;

ID3D11InputLayout* g_pLayout = nullptr;

Core::Core()
{
}


Core::~Core()
{
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

	FilePathSearch::Init();

	// Create Vertex Buffer
	g_arrVtx[0].vPos = DirectX::XMFLOAT3(0.f, 1.f, 0.5f);
	g_arrVtx[0].vColor = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);

	g_arrVtx[1].vPos = DirectX::XMFLOAT3(1.f, 0.f, 0.5f);
	g_arrVtx[1].vColor = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);

	g_arrVtx[2].vPos = DirectX::XMFLOAT3(-1.f, 0.f, 0.5f);
	g_arrVtx[2].vColor = DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.f);

	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = sizeof(TVertex) * 3;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_arrVtx; // 전역변수에 저장해둔 정점 정보를 GPU 메모리 초기값으로 전달

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tSub, &g_pVB);


	// Shader 만들기
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
	Device::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device::GetInstance()->GetContext()->IASetInputLayout(g_pLayout);

	Device::GetInstance()->GetContext()->VSSetShader(g_pVtxShader, nullptr, 0);
	Device::GetInstance()->GetContext()->PSSetShader(g_pPixelShader, nullptr, 0);
	Device::GetInstance()->GetContext()->Draw((UINT)3, (UINT)0);

	Device::GetInstance()->Present();

}
