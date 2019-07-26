#pragma once
class Device
{
private:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;

	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;

	ID3D11Texture2D* m_pDepthStencilTexture;
	ID3D11DepthStencilView* m_pDepthStencilView;

	UINT m_uiQuality;

	std::map<std::wstring, TConstantBuffer>	m_mapConstantBuffer;
	TResolution                    m_tRes;
public:
	TTransform g_tTransform;

public:
	Device();
	~Device();

public:
	int Init(HWND hWnd, const TResolution tRes, bool bWindowed);
	
	void Clear(float(&_fColor)[4])
	{
		m_pContext->ClearRenderTargetView(m_pRenderTargetView, _fColor);
		m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
		// 깊이 초기화 값은 최대값 1로 초기화
		// 깊이를 통과하기 위해서는 물체의 깊이가 더 가까워야 하기 때문에,
		// 그려지기 전에 초기화를 최대 깊으로 설정 해 둔다.
	}

	void Present()
	{
		m_pSwapChain->Present(0, 0);
	}
	
	ID3D11Device* GetDevice()
	{
		return m_pDevice;
	}

	const TResolution& GetResolution() { return m_tRes; }

	ID3D11DeviceContext* GetContext()
	{
		return m_pContext;
	}

	static Device* GetInstance()
	{
		static Device instance;
		return &instance;
	}

	void CreateConstBuffer(const std::wstring& _strKey, UINT _iSize, UINT _iRegister);
	TConstantBuffer& FindConstBuffer(const std::wstring& _strKey);

};

