#pragma once

class CSamplerState;
class CBlendState;
class CLight3D;

class CRenderMgr
{
	SINGLE(CRenderMgr);
private:
	CSamplerState*			m_arrSampler[(UINT)SAMPLER_TYPE::END];
	CBlendState*			m_arrBlendState[(UINT)BLEND_TYPE::END];
	ID3D11RasterizerState*  m_arrRSState[(UINT)RS_TYPE::END];

	tLight3DInfo			m_arrLight3DInfo[100];
	int						m_iLight3DCount;
	
public:
	void init();
	void render();
	void render_tool();

public:
	CBlendState* GetBlendState(BLEND_TYPE _eType) { return m_arrBlendState[(UINT)_eType]; }

public:
	void RegisterLight3D(const tLight3DInfo& _info) { m_arrLight3DInfo[m_iLight3DCount++] = _info; }
	void SetRSState(RS_TYPE _eType);

private:
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRSState();
	void UpdateLight3D();
};

