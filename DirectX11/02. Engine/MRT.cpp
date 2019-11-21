#include "stdafx.h"
#include "MRT.h"

#include "Device.h"
#include "RenderTarget23.h"
#include "Texture.h"

CMRT::CMRT()
{
}

CMRT::~CMRT()
{
}

void CMRT::Create(CRenderTarget23 *(&_arrRT)[8], CResPtr<CTexture> _pDepthTex)
{
	memcpy(m_arrRT, _arrRT, sizeof(void*) * 8);
	m_pDepthTex = _pDepthTex;

	for (m_iRTCount = 0; m_iRTCount < 8; ++m_iRTCount)
	{
		if (nullptr == _arrRT[m_iRTCount])
			break;
	}
}

void CMRT::OMSet()
{
	ID3D11RenderTargetView* arrView[8] = {};

	for (int i = 0; i < m_iRTCount; ++i)
	{
		arrView[i] = m_arrRT[i]->GetRTTex()->GetRTV();
	}

	CONTEXT->OMSetRenderTargets(m_iRTCount, arrView, m_pDepthTex->GetDSV());
}

void CMRT::clear()
{
	for (UINT i = 0; i < m_iRTCount; ++i)
	{
		m_arrRT[i]->clear();
	}

	CONTEXT->ClearDepthStencilView(m_pDepthTex->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);	
}