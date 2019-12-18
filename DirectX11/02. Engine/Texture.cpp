#include "stdafx.h"
#include "Texture.h"

#include "Device.h"
#include "ResMgr.h"

CTexture::CTexture()
	: m_pSRV(nullptr)
	, m_pTex2D(nullptr)
	, m_pRTV(nullptr)
	, m_pUAV(nullptr)
	, m_pDSV(nullptr)
	, CResource(RES_TYPE::TEXTURE)
{
}

CTexture::~CTexture()
{
	SAFE_RELEASE(m_pSRV);
	SAFE_RELEASE(m_pRTV);
	SAFE_RELEASE(m_pDSV);
	SAFE_RELEASE(m_pUAV);
	SAFE_RELEASE(m_pTex2D);
}

void CTexture::Load(const wstring & _strFilePath)
{
	// Texture 를 SystemMem 에 Loading
	wchar_t szExt[256] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 256);
	
	HRESULT hRet = S_OK;

	// dds
	if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))
	{
		hRet = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS_NONE, nullptr, m_Image);
	}
	// tga
	else if (!wcscmp(szExt, L".tga") || !wcscmp(szExt, L".TGA"))
	{
		hRet = LoadFromTGAFile(_strFilePath.c_str(), nullptr, m_Image);
	}
	else // png, jpg, jpeg, bmp
	{
		hRet = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS_NONE, nullptr, m_Image);
	}

	if (FAILED(CreateShaderResourceView(DEVICE
		, m_Image.GetImages()
		, m_Image.GetImageCount()
		, m_Image.GetMetadata()
		, &m_pSRV)))
	{
		MessageBox(nullptr, L"Fail Texture Load", L"텍스쳐 로딩 실패", MB_OK);
	}
			
	m_pSRV->GetResource(((ID3D11Resource**)&m_pTex2D));
	m_pTex2D->GetDesc(&m_tDesc);
}

void * CTexture::GetSysMem()
{
	CaptureTexture(DEVICE, CONTEXT, m_pTex2D, m_Image);
	return m_Image.GetPixels();
}

void CTexture::SetRegister(UINT _iRegister, UINT _iShaderType)
{
	if ((UINT)SHADER_TYPE::VERTEX_SHADER & _iShaderType)
		CONTEXT->VSSetShaderResources(_iRegister, 1, &m_pSRV);
	if ((UINT)SHADER_TYPE::HULL_SHADER & _iShaderType)
		CONTEXT->HSSetShaderResources(_iRegister, 1, &m_pSRV);
	if ((UINT)SHADER_TYPE::DOMAIN_SHADER & _iShaderType)
		CONTEXT->DSSetShaderResources(_iRegister, 1, &m_pSRV);
	if ((UINT)SHADER_TYPE::GEOMETRY_SHADER & _iShaderType)
		CONTEXT->GSSetShaderResources(_iRegister, 1, &m_pSRV);
	if ((UINT)SHADER_TYPE::COMPUTE_SHADER & _iShaderType)
		CONTEXT->CSSetShaderResources(_iRegister, 1, &m_pSRV);
	if ((UINT)SHADER_TYPE::PIXEL_SHADER & _iShaderType)
		CONTEXT->PSSetShaderResources(_iRegister, 1, &m_pSRV);
}

void CTexture::SetRegisterAll(UINT _iRegister)
{
	CONTEXT->VSSetShaderResources(_iRegister, 1, &m_pSRV);
	CONTEXT->PSSetShaderResources(_iRegister, 1, &m_pSRV);
}

bool CTexture::LoadFromScene(FILE * _pFile)
{
	CResource::LoadFromScene(_pFile);

	CResPtr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(GetName().c_str());
	if (nullptr != pTex)
		return false;

	wstring strPath = CPathMgr::GetResPath();
	strPath += GetPath();
	Load(strPath);

	return true;
}

void CTexture::ClearRegister(UINT _iRegister, UINT _iShaderType)
{
	ID3D11ShaderResourceView* pView = nullptr;

	if ((UINT)SHADER_TYPE::VERTEX_SHADER & _iShaderType)
		CONTEXT->VSSetShaderResources(_iRegister, 1, &pView);
	if ((UINT)SHADER_TYPE::HULL_SHADER & _iShaderType)
		CONTEXT->HSSetShaderResources(_iRegister, 1, &pView);
	if ((UINT)SHADER_TYPE::DOMAIN_SHADER & _iShaderType)
		CONTEXT->DSSetShaderResources(_iRegister, 1, &pView);
	if ((UINT)SHADER_TYPE::GEOMETRY_SHADER & _iShaderType)
		CONTEXT->GSSetShaderResources(_iRegister, 1, &pView);
	if ((UINT)SHADER_TYPE::COMPUTE_SHADER & _iShaderType)
		CONTEXT->CSSetShaderResources(_iRegister, 1, &pView);
	if ((UINT)SHADER_TYPE::PIXEL_SHADER & _iShaderType)
		CONTEXT->PSSetShaderResources(_iRegister, 1, &pView);
}

void CTexture::ClearAllRegister()
{
	const UINT iRegisterCount = (UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0;

	ID3D11ShaderResourceView* arrView[iRegisterCount] = {};
	CONTEXT->VSSetShaderResources(0, iRegisterCount, arrView);
	CONTEXT->HSSetShaderResources(0, iRegisterCount, arrView);
	CONTEXT->DSSetShaderResources(0, iRegisterCount, arrView);
	CONTEXT->GSSetShaderResources(0, iRegisterCount, arrView);
	CONTEXT->CSSetShaderResources(0, iRegisterCount, arrView);
	CONTEXT->PSSetShaderResources(0, iRegisterCount, arrView);

	const UINT iRWRegisterCount = (UINT)SHADER_PARAM::RWTEX_END - (UINT)SHADER_PARAM::RWTEX_0;
	ID3D11UnorderedAccessView* arrUAV[iRWRegisterCount] = {};
	CONTEXT->CSSetUnorderedAccessViews(0, iRWRegisterCount, arrUAV, nullptr);
}

void CTexture::SetRWRegister(UINT _iRegister)
{
	UINT i = -1;
	CONTEXT->CSSetUnorderedAccessViews(_iRegister, 1, &m_pUAV, &i);
}

void CTexture::ClearRWRegister(UINT _iRegister)
{
	ID3D11UnorderedAccessView* pUAV = nullptr;
	UINT i = -1;
	CONTEXT->CSSetUnorderedAccessViews(_iRegister, 1, &pUAV, &i);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight, UINT _iBindFlag, D3D11_USAGE _eUsage, DXGI_FORMAT _eFormat)
{
	// DepthStencil Texture
	// RenderTarget 과 같은 해상도로 설정
	m_tDesc.Width = _iWidth;
	m_tDesc.Height = _iHeight;
	m_tDesc.MipLevels = 1;
	m_tDesc.ArraySize = 1;
	m_tDesc.Format = _eFormat;
	m_tDesc.SampleDesc.Count = 1;
	m_tDesc.SampleDesc.Quality = 0;
	m_tDesc.Usage = _eUsage;			// 메모리 사용 용도(읽기, 쓰기 관련)
	m_tDesc.BindFlags = _iBindFlag;  // Texture  가 DepthStencil 용도로 사용될 것을 알림

	DEVICE->CreateTexture2D(&m_tDesc, nullptr, &m_pTex2D);

	// DepthStencil View
	if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{
		DEVICE->CreateDepthStencilView(m_pTex2D, nullptr, &m_pDSV);
	}
	else
	{
		if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			DEVICE->CreateRenderTargetView(m_pTex2D, nullptr, &m_pRTV);
		}

		if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			DEVICE->CreateShaderResourceView(m_pTex2D, nullptr, &m_pSRV);
		}

		if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			DEVICE->CreateUnorderedAccessView(m_pTex2D, nullptr, &m_pUAV);
		}
	}
}

void CTexture::Create(ID3D11Texture2D * _pTex2D)
{
	m_pTex2D = _pTex2D;

	m_pTex2D->GetDesc(&m_tDesc);

	// DepthStencil View
	if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{
		DEVICE->CreateDepthStencilView(m_pTex2D, nullptr, &m_pDSV);
	}
	else
	{
		if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			DEVICE->CreateRenderTargetView(m_pTex2D, nullptr, &m_pRTV);
		}

		if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			DEVICE->CreateShaderResourceView(m_pTex2D, nullptr, &m_pSRV);
		}

		if (m_tDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			DEVICE->CreateUnorderedAccessView(m_pTex2D, nullptr, &m_pUAV);
		}
	}
}
