#pragma once

class CSamplerState;
class CBlendState;
class CLight3D;
class CRenderTarget23;
class CMRT;
class CCamera;

class CRenderMgr
{
	SINGLE(CRenderMgr);
private:
	HWND					m_hWnd;		// ��� ������ �ڵ�
	tResolution				m_tRes;		// ������ �ػ�

	CSamplerState*			m_arrSampler[(UINT)SAMPLER_TYPE::END];
	CBlendState*			m_arrBlendState[(UINT)BLEND_TYPE::END];
	ID3D11RasterizerState*  m_arrRSState[(UINT)RS_TYPE::END];

	CRenderTarget23*		m_arrRT[(UINT)RT_TYPE::END];
	CMRT*					m_arrMRT[(UINT)MRT_TYPE::END];

	IDXGISwapChain*			m_pSwapChain;			// SwapChain ��� ���

	tLight3DInfo			m_arrLight3DInfo[100];	// Scene �� �ִ� ����
	int						m_iLight3DCount;
	vector<CLight3D*>		m_vecLight3D;

	vector<CCamera*>		m_vecCam;				// Scene �� �ִ� ī�޶�

	bool					m_bWindow;

public:
	void init(HWND _hWnd, tResolution _tres, bool _bWindow);
	void render();
	void render_tool();
	void render_lights();

public:
	CBlendState* GetBlendState(BLEND_TYPE _eType) { return m_arrBlendState[(UINT)_eType]; }
	CMRT* GetMRT(MRT_TYPE _eType) { return m_arrMRT[(UINT)_eType]; }

public:
	void RegisterLight3D(CLight3D* _pLight3D);
	void RegisterCamera(CCamera* _pCam) { m_vecCam.push_back(_pCam); }
	void ClearRegisterObj()
	{
		m_vecCam.clear(); 
		m_vecLight3D.clear();
		m_iLight3DCount = 0;
	}
	void SetRSState(RS_TYPE _eType);
	void Present() { m_pSwapChain->Present(0, 0); }
	void Clear();
	tResolution GetResolution() { return m_tRes; }

private:
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRSState();
	void CreateRenderTarget();
	void UpdateLight3D();
};

