#include "stdafx.h"
#include "Device.h"


Device::Device()
{
	m_iQuality = 0;
}


Device::~Device()
{
	m_pDevice->Release();
	m_pContext->Release();

	m_pSwapChain->Release();
	m_pRenderTargetView->Release();

	m_pDepthStencilTexture->Release();
	m_pDepthStencilView->Release();
}

int Device::Init(HWND hWnd, const TResolution tRes, bool bWindowed)
{
	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL eLv = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL eOut = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		iFlag,
		&eLv,							//기능레벨에 대한 옵션값을 eLv에 대해서 주었더니 터진다.
		1,
		D3D11_SDK_VERSION,
		&m_pDevice,
		&eOut,
		&m_pContext
	)))
	{
		return E_FAIL;
	}

	// Multi Sample Level Check
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iQuality);
	assert(m_iQuality > 0);

	// Create SwapChain
	DXGI_SWAP_CHAIN_DESC tSwapDesc;
	tSwapDesc.BufferCount = 1;
	tSwapDesc.BufferDesc.Width = static_cast<UINT>(tRes.fWidth);
	tSwapDesc.BufferDesc.Height = static_cast<UINT>(tRes.fHeight);
	tSwapDesc.BufferDesc.RefreshRate.Numerator = 60;
	tSwapDesc.BufferDesc.RefreshRate.Denominator = 1;
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapDesc.SampleDesc.Count = 4;
	tSwapDesc.SampleDesc.Quality = m_iQuality - 1;			//앞서 조사한 멀티샘플링에 대한 퀼리티값에서 1를 뺀 값이 들어가야한다.
	tSwapDesc.OutputWindow = hWnd;
	tSwapDesc.Windowed = bWindowed;
	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	tSwapDesc.Flags = 0;

	IDXGIDevice* pIDXDevice = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIFactory* pFactory = nullptr;
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pIDXDevice);
	pIDXDevice->GetAdapter(&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	HRESULT hr = pFactory->CreateSwapChain(m_pDevice, &tSwapDesc, &m_pSwapChain);

	// 참조 Count 줄여주기
	pIDXDevice->Release();
	pAdapter->Release();
	pFactory->Release();
	
	// RenderTarget View
	// SwapChain 이 가지고 있는 RenderTarget 용 Texture 를 얻어온다.
	ID3D11Texture2D* pRenderTargetTex = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pRenderTargetTex);
	pRenderTargetTex->Release();

	// SwapChain 의 RenderTarget 용 Texture 를 이용해서 RenderTargetView 를 만듬
	m_pDevice->CreateRenderTargetView(pRenderTargetTex, nullptr, &m_pRenderTargetView);

	// DepthStencil Texture
	D3D11_TEXTURE2D_DESC tTexDesc = {};

	// RenderTarget 과 같은 해상도로 설정
	tTexDesc.Width = static_cast<UINT>(tRes.fWidth);
	tTexDesc.Height = static_cast<UINT>(tRes.fHeight);
	tTexDesc.MipLevels = 1;
	tTexDesc.ArraySize = 1;
	tTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tTexDesc.SampleDesc.Count = 4;
	tTexDesc.SampleDesc.Quality = m_iQuality - 1;
	tTexDesc.Usage = D3D11_USAGE_DEFAULT;			// 메모리 사용 용도(읽기, 쓰기 관련)
	tTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;  // Texture  가 DepthStencil 용도로 사용될 것을 알림

	m_pDevice->CreateTexture2D(&tTexDesc, nullptr, &m_pDepthStencilTexture);

	// DepthStencil View
	m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, nullptr, &m_pDepthStencilView);

	// Output Merget State 에 RenderTagetView, DepthStencilView 전달
	// OM 단계에 전달할 수 있는 최대 RenderTargetView 개수는 dx11 기준 8개 이다.
	// 따라서 OMSetRenderTargets 함수는 RenderTargetView* 배열을 요구한다
	m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	// ViewPort
	D3D11_VIEWPORT tVP = {};

	tVP.Width = static_cast<FLOAT>(tRes.fWidth);
	tVP.Height = static_cast<FLOAT>(tRes.fHeight);

	tVP.TopLeftX = 0;
	tVP.TopLeftY = 0;

	tVP.MinDepth = 0.f;
	tVP.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &tVP);



	return S_OK;
}
