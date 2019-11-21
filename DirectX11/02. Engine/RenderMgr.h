#pragma once

class CSamplerState;
class CBlendState;
class CLight3D;
class CRenderTarget23;
class CMRT;

class CRenderMgr
{
	SINGLE(CRenderMgr);
private:
	HWND					m_hWnd;		// 출력 윈도우 핸들
	tResolution				m_tRes;		// 윈도우 해상도

	CSamplerState*			m_arrSampler[(UINT)SAMPLER_TYPE::END];
	CBlendState*			m_arrBlendState[(UINT)BLEND_TYPE::END];
	ID3D11RasterizerState*  m_arrRSState[(UINT)RS_TYPE::END];

	CRenderTarget23*		m_arrRT[(UINT)RT_TYPE::END];
	CMRT*					m_arrMRT[(UINT)MRT_TYPE::END];


	IDXGISwapChain*				m_pSwapChain;			// SwapChain 기능 담당


	tLight3DInfo			m_arrLight3DInfo[100];
	int						m_iLight3DCount;
	bool					m_bWindow;

public:
	void init(HWND _hWnd, tResolution _tres, bool _bWindow);
	void render();
	void render_tool();

public:
	CBlendState* GetBlendState(BLEND_TYPE _eType) { return m_arrBlendState[(UINT)_eType]; }

public:
	void RegisterLight3D(const tLight3DInfo& _info) { m_arrLight3DInfo[m_iLight3DCount++] = _info; }
	void SetRSState(RS_TYPE _eType);
	void Present() { m_pSwapChain->Present(0, 0); }

	tResolution GetResolution() { return m_tRes; }

	void Clear();

private:
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRSState();
	void CreateRenderTarget();
	void UpdateLight3D();
};

