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

public:
	Device();
	~Device();

	int Init(HWND hWnd, const TResolution tRes, bool bWindowed);
	
	void Clear(float(&fColor)[4])
	{
		m_pContext->ClearRenderTargetView(m_pRenderTargetView, fColor);
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

	ID3D11DeviceContext* GetContext()
	{
		return m_pContext;
	}

	static Device* GetInstance()
	{
		static Device instance;
		return &instance;
	}
};

