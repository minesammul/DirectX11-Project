#include "stdafx.h"
#include "Device.h"

#include "ConstBuffer.h"
#include "ResMgr.h"

CDevice::CDevice()
	: m_pDevice(nullptr)
	, m_pContext(nullptr)
	, m_pSwapChain(nullptr)
	, m_pRenderTargetView(nullptr)
	, m_pDepthTex(nullptr)
	, m_iQuality(0)
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pContext);

	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);

	Safe_Delete_Map(m_mapConstBuffer);
}

int CDevice::init(HWND _hWnd, const tResolution& _tRes, bool _bWindowed)
{
	m_tRes = _tRes;

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL eLv = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL eOut = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
		
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, iFlag
		, &eLv, 1, D3D11_SDK_VERSION
		, &m_pDevice
		, &eOut
		, &m_pContext)))
	{
		return E_FAIL;
	}
	
	// Multi Sample Level Check
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iQuality);
	
	// Create SwapChain
	DXGI_SWAP_CHAIN_DESC tSwapDesc = {};

	tSwapDesc.BufferCount = 1;
	tSwapDesc.BufferDesc.Width = (UINT)_tRes.fWidth;
	tSwapDesc.BufferDesc.Height = (UINT)_tRes.fHeight;
	tSwapDesc.BufferDesc.RefreshRate.Numerator		= 60;
	tSwapDesc.BufferDesc.RefreshRate.Denominator	= 1;
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	tSwapDesc.SampleDesc.Count = 4;
	tSwapDesc.SampleDesc.Quality = 0;

	tSwapDesc.OutputWindow = _hWnd;	// ��� ������
	tSwapDesc.Windowed = _bWindowed;	

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
	SAFE_RELEASE(pIDXDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);
	
	// RenderTarget View
	// SwapChain �� ������ �ִ� RenderTarget �� Texture �� ���´�.
	ID3D11Texture2D* pRenderTargetTex = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pRenderTargetTex);
	SAFE_RELEASE(pRenderTargetTex); // ���� ref count �ϳ� �ٿ��ֱ�

	// SwapChain �� RenderTarget �� Texture �� �̿��ؼ� RenderTargetView �� ����
	m_pDevice->CreateRenderTargetView(pRenderTargetTex, nullptr, &m_pRenderTargetView);
	   
	   	 	
	m_pDepthTex = CResMgr::GetInst()->CreateTexture(L"DepthStencilTex", (UINT)_tRes.fWidth, (UINT)_tRes.fHeight
		, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, DXGI_FORMAT_D24_UNORM_S8_UINT);

	
	// Output Merget State �� RenderTagetView, DepthStencilView ����
	// OM �ܰ迡 ������ �� �ִ� �ִ� RenderTargetView ������ dx11 ���� 8�� �̴�.
	// ���� OMSetRenderTargets �Լ��� RenderTargetView* �迭�� �䱸�Ѵ�
	m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthTex->GetDSV());


	// ViewPort
	D3D11_VIEWPORT tVP = {};

	tVP.Width = _tRes.fWidth;
	tVP.Height = _tRes.fHeight;	

	tVP.TopLeftX = 0;
	tVP.TopLeftY = 0;

	tVP.MinDepth = 0.f;
	tVP.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &tVP);

	return S_OK;
}

void CDevice::CreateConstBuffer(const wstring & _strKey, UINT _iSize, UINT _iRegister)
{
	map<wstring, CConstBuffer*>::iterator iter = m_mapConstBuffer.find(_strKey);
	assert(iter == m_mapConstBuffer.end());

	CConstBuffer* pConstBuffer = new CConstBuffer;
	   
	pConstBuffer->Create(_iSize, _iRegister);
	pConstBuffer->SetName(_strKey);

	m_mapConstBuffer.insert(make_pair(_strKey, pConstBuffer));
}

CConstBuffer* CDevice::FindConstBuffer(const wstring & _strKey)
{
	return m_mapConstBuffer.find(_strKey)->second;
}
