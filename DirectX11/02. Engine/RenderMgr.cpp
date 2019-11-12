#include "stdafx.h"
#include "RenderMgr.h"

#include "SamplerState.h"
#include "BlendState.h"

#include "ConstBuffer.h"
#include "Device.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Light3D.h"

tGlobalValue g_global = {};

CRenderMgr::CRenderMgr()
	: m_arrSampler{}
	, m_arrBlendState{}
	, m_arrLight3DInfo{}
	, m_iLight3DCount(0)
{
}

CRenderMgr::~CRenderMgr()
{
	Safe_Delete_Array(m_arrSampler);
	Safe_Delete_Array(m_arrBlendState);
}

void CRenderMgr::init()
{
	CreateSamplerState();
	CreateBlendState();
}

void CRenderMgr::render()
{	
	// ��ġ ���� �ʱ�ȭ
	float arrCol[4] = { 0.6f, 0.6f, 0.6f, 1.f };
	CDevice::GetInst()->Clear(arrCol);

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
	CDevice::GetInst()->Present();
}

void CRenderMgr::render_tool()
{
	// ��ġ ���� �ʱ�ȭ
	float arrCol[4] = { 0.6f, 0.6f, 0.6f, 1.f };
	CDevice::GetInst()->Clear(arrCol);

	// ���� ���� ������ۿ� ������Ʈ
	UpdateLight3D();
}

void CRenderMgr::CreateSamplerState()
{
	D3D11_SAMPLER_DESC tDesc = {};

	m_arrSampler[(UINT)SAMPLER_TYPE::DEFAULT] = new CSamplerState;

	//tDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
	tDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
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