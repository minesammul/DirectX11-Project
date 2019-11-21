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
	UINT						m_iBindFlag;

public:
	virtual void Load(const wstring& _strFilePath);
	virtual void Create(UINT _iWidth, UINT _iHeight, UINT _iBindFlag, D3D11_USAGE _eUsage, DXGI_FORMAT _eFormat);
	virtual void Save() {};

public:
	float GetWidth() { return (float)m_Image.GetMetadata().width; }
	float GetHeight() { return (float)m_Image.GetMetadata().height; }

	ID3D11ShaderResourceView* GetSRV() { return m_pSRV; }
	ID3D11RenderTargetView* GetRTV() { return m_pRTV; }
	ID3D11DepthStencilView* GetDSV() { return m_pDSV; }

public:
	void SetRegister(UINT _iRegister, UINT _iShaderType);
	void SetRegisterAll(UINT _iRegister);

	virtual bool LoadFromScene(FILE* _pFile);

	static void ClearRegister(UINT _iRegister, UINT _iShaderType);

public:
	CTexture();
	virtual ~CTexture();
};

