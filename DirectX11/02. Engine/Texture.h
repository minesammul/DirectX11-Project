#pragma once

#include <DirectXTex.h>
#include <DirectXTex.inl>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug")
#else
#pragma comment(lib, "DirectXTex")
#endif

#include "Resource.h"

class CTexture :
	public CResource
{
private:
	ID3D11ShaderResourceView*	m_pSRV;
	ID3D11RenderTargetView*		m_pRTV;
	ID3D11DepthStencilView*		m_pDSV;

	ID3D11Texture2D*			m_pTex2D;
	ScratchImage				m_Image;
	D3D11_TEXTURE2D_DESC		m_tDesc;

public:
	virtual void Load(const wstring& _strFilePath);
	virtual void Create(UINT _iWidth, UINT _iHeight, UINT _iBindFlag, D3D11_USAGE _eUsage, DXGI_FORMAT _eFormat);
	virtual void Save() {};
	virtual void Create(ID3D11Texture2D* _pTex2D);

public:
	UINT GetWidth() { return m_tDesc.Width; }
	UINT GetHeight() { return m_tDesc.Height; }

	ID3D11ShaderResourceView* GetSRV() { return m_pSRV; }
	ID3D11RenderTargetView* GetRTV() { return m_pRTV; }
	ID3D11DepthStencilView* GetDSV() { return m_pDSV; }

public:
	void SetRegister(UINT _iRegister, UINT _iShaderType);
	void SetRegisterAll(UINT _iRegister);

	virtual bool LoadFromScene(FILE* _pFile);

	static void ClearRegister(UINT _iRegister, UINT _iShaderType);

	static void ClearAllRegister();

public:
	CTexture();
	virtual ~CTexture();
};

