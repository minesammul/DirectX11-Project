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
		// ���� �ʱ�ȭ ���� �ִ밪 1�� �ʱ�ȭ
		// ���̸� ����ϱ� ���ؼ��� ��ü�� ���̰� �� ������� �ϱ� ������,
		// �׷����� ���� �ʱ�ȭ�� �ִ� ������ ���� �� �д�.
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

