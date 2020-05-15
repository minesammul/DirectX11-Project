#pragma once

class CSamplerState;
class CBlendState;
class CDepthStencilState;
class CLight3D;
class CRenderTarget23;
class CMRT;
class CCamera;

#include "ResPtr.h"
#include "Filter23.h"

class CRenderMgr
{
	SINGLE(CRenderMgr);
private:
	HWND					m_hWnd;		// ��� ������ �ڵ�
	tResolution				m_tRes;		// ������ �ػ�
	IDXGISwapChain*			m_pSwapChain;			// SwapChain ��� ���
	bool					m_bWindow;

	CSamplerState*			m_arrSampler[(UINT)SAMPLER_TYPE::END];
	CBlendState*			m_arrBlendState[(UINT)BLEND_TYPE::END];
	CDepthStencilState*		m_arrDSState[(UINT)DEPTH_STENCIL_TYPE::END];
	ID3D11RasterizerState*  m_arrRSState[(UINT)RS_TYPE::END];

	CRenderTarget23*		m_arrRT[(UINT)RT_TYPE::END];
	CMRT*					m_arrMRT[(UINT)MRT_TYPE::END];

	tLight3DInfo			m_arrLight3DInfo[100];	// Scene �� �ִ� ����
	int						m_iLight3DCount;
	vector<CLight3D*>		m_vecLight3D;

	vector<CCamera*>		m_vecCam;				// Scene �� �ִ� ī�޶�

	CResPtr<CFilter23>      m_pMergeFilter;

	CCamera*				m_pToolCam;				// Tool �� ������ �ִ� Camera

public:
	void init(HWND _hWnd, tResolution _tres, bool _bWindow);
	void render();
	void render_tool();
	void render_lights();
	void render_shadowmap();
	void render_posteffect();

	void CopySwapToPosteffect();
	void CopyTempToBefore();
	void CopySwapToTemp();

public:
	CBlendState* GetBlendState(BLEND_TYPE _eType) { return m_arrBlendState[(UINT)_eType]; }
	CDepthStencilState* GetDepthStencilState(DEPTH_STENCIL_TYPE _eType) { return m_arrDSState[(UINT)_eType]; }
	CMRT* GetMRT(MRT_TYPE _eType) { return m_arrMRT[(UINT)_eType]; }
	void SetMergeFilter(CResPtr<CFilter23> _pFilter) { m_pMergeFilter = _pFilter; }

public:
	int RegisterLight3D(CLight3D* _pLight3D);
	void RegisterCamera(CCamera* _pCam) { m_vecCam.push_back(_pCam); }
	void ClearRegisterObj()
	{
		m_vecCam.clear(); 
		m_vecLight3D.clear();
		m_iLight3DCount = 0;
	}
	void SetRSState(RS_TYPE _eType);
	void SetToolCam(CCamera* _pCam) { m_pToolCam = _pCam; }
	void Present() { m_pSwapChain->Present(0, 0); }
	void Clear();
	tResolution GetResolution() { return m_tRes; }
	CCamera* GetMainCam();

private:
	void CreateSamplerState();
	void CreateBlendState();
	void CreateDepthStencilState();
	void CreateRSState();
	void CreateRenderTarget();
	void UpdateLight3D();
};

