#include "stdafx.h"
#include "RenderMgr.h"

#include "SamplerState.h"
#include "BlendState.h"

#include "ConstBuffer.h"
#include "Device.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Light3D.h"
#include "ResMgr.h"
#include "Texture.h"

#include "RenderTarget23.h"
#include "MRT.h"

tGlobalValue g_global = {};

CRenderMgr::CRenderMgr()
	: m_arrSampler{}
	, m_arrBlendState{}
	, m_arrRSState{}
	, m_arrRT{}
	, m_arrLight3DInfo{}
	, m_pSwapChain(nullptr)
	, m_iLight3DCount(0)
	, m_bWindow(false)
{
}

CRenderMgr::~CRenderMgr()
{
	Safe_Delete_Array(m_arrSampler);
	Safe_Delete_Array(m_arrBlendState);
	Safe_Release_Array(m_arrRSState);

	Safe_Delete_Array(m_arrMRT);
	Safe_Delete_Array(m_arrRT);

	SAFE_RELEASE(m_pSwapChain)
}

void CRenderMgr::init(HWND _hWnd, tResolution _tres, bool _bWindow)
{
	m_hWnd = _hWnd;
	m_tRes = _tres;
	m_bWindow = _bWindow;


	CreateSamplerState();
	CreateBlendState();
	CreateRSState();
	CreateRenderTarget();

	// ViewPort
	D3D11_VIEWPORT tVP = {};

	tVP.Width = m_tRes.fWidth;
	tVP.Height = m_tRes.fHeight;

	tVP.TopLeftX = 0;
	tVP.TopLeftY = 0;

	tVP.MinDepth = 0.f;
	tVP.MaxDepth = 1.f;

	CONTEXT->RSSetViewports(1, &tVP);
}

void CRenderMgr::render()
{	
	Clear();

	{
		static CConstBuffer* pGlobal = CDevice::GetInst()->FindConstBuffer(L"Global");
		pGlobal->AddData(&g_global, sizeof(tGlobalValue));
		pGlobal->UpdateData();
		pGlobal->SetRegisterAll();

		// ���� ���� ������ۿ� ������Ʈ
		UpdateLight3D();

		CSceneMgr::GetInst()->render();
	}
	

	// �����쿡 ���
	Present();
}

void CRenderMgr::render_tool()
{
	// ��ġ ���� �ʱ�ȭ
	Clear();

	// ���� ���� ������ۿ� ������Ʈ
	UpdateLight3D();
}

void CRenderMgr::SetRSState(RS_TYPE _eType)
{
	CONTEXT->RSSetState(m_arrRSState[(UINT)_eType]);
}

void CRenderMgr::Clear()
{
	for (UINT i = 0; i < (UINT)MRT_TYPE::END; ++i)
	{
		if (nullptr != m_arrMRT[i])
			m_arrMRT[i]->clear();
	}
}

void CRenderMgr::CreateSamplerState()
{
	D3D11_SAMPLER_DESC tDesc = {};

	m_arrSampler[(UINT)SAMPLER_TYPE::DEFAULT] = new CSamplerState;

	tDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
	//tDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	tDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	m_arrSampler[(UINT)SAMPLER_TYPE::DEFAULT]->Create(&tDesc, 0);
	m_arrSampler[(UINT)SAMPLER_TYPE::DEFAULT]->UpdateData();
}

void CRenderMgr::CreateBlendState()
{
	D3D11_BLEND_DESC tDesc = {};

	// ====================
	// Default Blend State
	// ====================
	m_arrBlendState[(UINT)BLEND_TYPE::DEFAULT] = new CBlendState;
	
	// =================
	// Alpha Blend State
	// =================
	m_arrBlendState[(UINT)BLEND_TYPE::ALPHABLEND] = new CBlendState;

	tDesc.AlphaToCoverageEnable = true;   // ����ü ���ǿ� ���ؼ� �������� ���� ����(x4 ��Ƽ������ ������ ���)
	tDesc.IndependentBlendEnable = false; // ����Ÿ�� ���� �������� ���� ���� ���
	
	tDesc.RenderTarget[0].BlendEnable = true;

	// ���� ȥ�� ����
	tDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlend	= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	tDesc.RenderTarget[0].DestBlend	= D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

	// Alpha �� ���� ȥ�հ���
	tDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	tDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;	

	tDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	m_arrBlendState[(UINT)BLEND_TYPE::ALPHABLEND]->Create(&tDesc);
}

void CRenderMgr::UpdateLight3D()
{
	static CConstBuffer* pLightBuffer = CDevice::GetInst()->FindConstBuffer(L"Light3D");

	pLightBuffer->AddData(m_arrLight3DInfo, sizeof(tLight3DInfo) * 100);
	pLightBuffer->AddData(&m_iLight3DCount, sizeof(int));
	pLightBuffer->UpdateData();
	pLightBuffer->SetRegisterAll();

	m_iLight3DCount = 0;
}

void CRenderMgr::CreateRSState()
{
	// Rasterizer State
	m_arrRSState[(UINT)RS_TYPE::CULL_BACK] = nullptr;

	ID3D11RasterizerState* pRSState = nullptr;
	D3D11_RASTERIZER_DESC tRSDesc = {};
	tRSDesc.CullMode = D3D11_CULL_FRONT;
	tRSDesc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&tRSDesc, &pRSState);
	m_arrRSState[(UINT)RS_TYPE::CULL_FRONT] = pRSState;

	tRSDesc.CullMode = D3D11_CULL_NONE;
	tRSDesc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&tRSDesc, &pRSState);
	m_arrRSState[(UINT)RS_TYPE::CULL_NONE] = pRSState;

	tRSDesc.CullMode = D3D11_CULL_NONE;
	tRSDesc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&tRSDesc, &pRSState);
	m_arrRSState[(UINT)RS_TYPE::WIREFRAME] = pRSState;
}

void CRenderMgr::CreateRenderTarget()
{
	// Create SwapChain
	DXGI_SWAP_CHAIN_DESC tSwapDesc = {};

	tSwapDesc.BufferCount = 1;
	tSwapDesc.BufferDesc.Width = (UINT)m_tRes.fWidth;
	tSwapDesc.BufferDesc.Height = (UINT)m_tRes.fHeight;
	tSwapDesc.BufferDesc.RefreshRate.Numerator = 60;
	tSwapDesc.BufferDesc.RefreshRate.Denominator = 1;
	tSwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	tSwapDesc.SampleDesc.Count = 4;
	tSwapDesc.SampleDesc.Quality = 0;

	tSwapDesc.OutputWindow = m_hWnd;	// ��� ������
	tSwapDesc.Windowed = m_bWindow;

	tSwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	tSwapDesc.Flags = 0;

	IDXGIDevice* pIDXDevice = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIFactory* pFactory = nullptr;

	DEVICE->QueryInterface(__uuidof(IDXGIDevice), (void**)&pIDXDevice);
	pIDXDevice->GetAdapter(&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	HRESULT hr = pFactory->CreateSwapChain(DEVICE, &tSwapDesc, &m_pSwapChain);

	// ���� Count �ٿ��ֱ�
	SAFE_RELEASE(pIDXDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	// RenderTarget View
	// SwapChain �� ������ �ִ� RenderTarget �� Texture �� ���´�.
	ID3D11Texture2D* pRenderTargetTex = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pRenderTargetTex);
	CResPtr<CTexture> pSwapChainTex = CResMgr::GetInst()->CreateTexture(L"SwapChainTex", pRenderTargetTex);

	// DepthStencil Texture
	CResPtr<CTexture> pDepthTex = CResMgr::GetInst()->CreateTexture(L"DepthStencilTex", (UINT)m_tRes.fWidth, (UINT)m_tRes.fHeight
		, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, DXGI_FORMAT_D24_UNORM_S8_UINT);

	// =======================
	// SwapChain RenderTarget
	// =======================
	m_arrRT[(UINT)RT_TYPE::SWAPCHAIN] = new CRenderTarget23;
	m_arrRT[(UINT)RT_TYPE::SWAPCHAIN]->Create(L"SwapChainTarget", pSwapChainTex, Vec4(0.f, 0.f, 0.f, 0.f));

	// =============
	// Swapchain MRT
	// =============
	CRenderTarget23* rt[8] = { m_arrRT[(UINT)RT_TYPE::SWAPCHAIN] , };
	m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN] = new CMRT;
	m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->Create(rt, pDepthTex);

	m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->OMSet();
}