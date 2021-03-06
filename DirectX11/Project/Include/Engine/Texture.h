#pragma once

#include <DirectXTex.h>
#include <DirectXTex.inl>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug")
#else
#pragma comment(lib, "DirectXTex")
#endif

#include "Resource.h"
#include "ResPtr.h"

class CMaterial;

class CTexture :
	public CResource
{
public:
	static CMaterial*		g_pClearMtrl;

private:
	ID3D11ShaderResourceView*	m_pSRV;
	ID3D11UnorderedAccessView*  m_pUAV;
	ID3D11RenderTargetView*		m_pRTV;
	ID3D11DepthStencilView*		m_pDSV;

	ID3D11Texture2D*			m_pTex2D;
	ScratchImage				m_Image;
	D3D11_TEXTURE2D_DESC		m_tDesc;

public:
	virtual void Load(const wstring& _strFilePath);
	void Save(const wstring& _strPath);
	void Create(UINT _iWidth, UINT _iHeight, UINT _iBindFlag, D3D11_USAGE _eUsage, DXGI_FORMAT _eFormat);
	void Create(ID3D11Texture2D* _pTex2D);
	void CreateArrayTexture(vector <CResPtr<CTexture>>& _vecTex);


public:
	ID3D11Texture2D* GetTexture2D(){ return m_pTex2D; }
	void SetTexture2D(ID3D11Texture2D* data) { m_pTex2D = data; }

	UINT GetWidth() { return m_tDesc.Width; }
	UINT GetHeight() { return m_tDesc.Height; }

	size_t GetRowPitch() { return m_Image.GetImages()->rowPitch; }
	size_t GetSlicePitch() { return m_Image.GetImages()->slicePitch; }

	ID3D11ShaderResourceView* GetSRV() { return m_pSRV; }
	ID3D11RenderTargetView* GetRTV() { return m_pRTV; }
	ID3D11DepthStencilView* GetDSV() { return m_pDSV; }
	ID3D11UnorderedAccessView* GetUAV() { return m_pUAV; }

	ID3D11Texture2D* GetTex2D() { return m_pTex2D; }

	const D3D11_TEXTURE2D_DESC& GetDesc() { return m_tDesc; }

	void* GetSysMem();
	void Clear(); // Dynammic flag, cpuaccesswrite, bindflag shaderresource only
	void RWClear(Vec4 _vClearColor); // unorderedaccessview only
	void Capture();

public:
	void SetRegister(UINT _iRegister, UINT _iShaderType);
	void SetRegisterAll(UINT _iRegister);

	static void ClearRegister(UINT _iRegister, UINT _iShaderType);
	static void ClearAllRegister();

	void SetData(void * _pSrc, size_t _size); // 20200102 �߰�	
	void Resize(UINT _iWidth, UINT _iHeight); // 20200102 �߰�


	void SetRWRegister(UINT _iRegister);
	static void ClearRWRegister(UINT _iRegister);

	virtual bool LoadFromScene(FILE* _pFile);

public:
	CTexture();
	virtual ~CTexture();
};

