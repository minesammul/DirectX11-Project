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

	Device::GetInstance()->GetContext()->VSSetShader(g_pVtxShader, nullptr, 0);
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

	Device::GetInstance()->Present();

}
