#include "stdafx.h"
#include "Device.h"


Device::Device()
	: m_pDevice(nullptr)
	, m_pContext(nullptr)
	, m_pSwapChain(nullptr)
	, m_pRenderTargetView(nullptr)
	, m_pDepthStencilTexture(nullptr)
	, m_pDepthStencilView(nullptr)
	, m_uiQuality(0)
{

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
	m_tRes = tRes;

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
		&eLv,							//��ɷ����� ���� �ɼǰ��� eLv�� ���ؼ� �־����� ������.
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
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_uiQuality);
	assert(m_uiQuality > 0);

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
	tSwapDesc.SampleDesc.Quality = m_uiQuality - 1;			//�ռ� ������ ��Ƽ���ø��� ���� ����Ƽ������ 1�� �� ���� �����Ѵ�.
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

	// ���� Count �ٿ��ֱ�
	pIDXDevice->Release();
	pAdapter->Release();
	pFactory->Release();
	
	// RenderTarget View
	// SwapChain �� ������ �ִ� RenderTarget �� Texture �� ���´�.
	ID3D11Texture2D* pRenderTargetTex = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pRenderTargetTex);
	pRenderTargetTex->Release();

	// SwapChain �� RenderTarget �� Texture �� �̿��ؼ� RenderTargetView �� ����
	m_pDevice->CreateRenderTargetView(pRenderTargetTex, nullptr, &m_pRenderTargetView);

	// DepthStencil Texture
	D3D11_TEXTURE2D_DESC tTexDesc = {};

	// RenderTarget �� ���� �ػ󵵷� ����
	tTexDesc.Width = static_cast<UINT>(tRes.fWidth);
	tTexDesc.Height = static_cast<UINT>(tRes.fHeight);
	tTexDesc.MipLevels = 1;
	tTexDesc.ArraySize = 1;
	tTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tTexDesc.SampleDesc.Count = 4;
	tTexDesc.SampleDesc.Quality = m_uiQuality - 1;
	tTexDesc.Usage = D3D11_USAGE_DEFAULT;			// �޸� ��� �뵵(�б�, ���� ����)
	tTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;  // Texture  �� DepthStencil �뵵�� ���� ���� �˸�

	m_pDevice->CreateTexture2D(&tTexDesc, nullptr, &m_pDepthStencilTexture);

	// DepthStencil View
	m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, nullptr, &m_pDepthStencilView);

	// Output Merget State �� RenderTagetView, DepthStencilView ����
	// OM �ܰ迡 ������ �� �ִ� �ִ� RenderTargetView ������ dx11 ���� 8�� �̴�.
	// ���� OMSetRenderTargets �Լ��� RenderTargetView* �迭�� �䱸�Ѵ�
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

void Device::CreateConstBuffer(const std::wstring & _strKey, UINT _iSize, UINT _iRegister)
{
	std::map<std::wstring, TConstantBuffer>::iterator iter = m_mapConstantBuffer.find(_strKey);
	assert(iter == m_mapConstantBuffer.end());

	// Create Const Buffer
	D3D11_BUFFER_DESC tBufferDesc = {};
	ID3D11Buffer* pBuffer = nullptr;

	tBufferDesc.ByteWidth = _iSize;
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Device::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, nullptr, &pBuffer);

	TConstantBuffer tCB = {};
	tCB.pBuffer = pBuffer;
	tCB.uiSize = _iSize;
	tCB.uiRegister = _iRegister;

	m_mapConstantBuffer.insert(make_pair(_strKey, tCB));

}

TConstantBuffer & Device::FindConstBuffer(const std::wstring & _strKey)
{
	return m_mapConstantBuffer.find(_strKey)->second;
}
