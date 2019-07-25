#include "stdafx.h"
#include "Shader.h"
#include "FilePathSearch.h"
#include "Device.h"

Shader::Shader()
	: m_pVertexShaderBlob(nullptr)
	, m_pHullShaderBlob(nullptr)
	, m_pDomainShaderBlob(nullptr)
	, m_pGeometryShaderBlob(nullptr)
	, m_pPixelShaderBlob(nullptr)
	, m_pErrorBlob(nullptr)
	, m_pVertexShader(nullptr)
	, m_pHullShader(nullptr)
	, m_pDomainShader(nullptr)
	, m_pGeometryShader(nullptr)
	, m_pPixelShader(nullptr)
{
}


Shader::~Shader()
{
	m_pVertexShaderBlob->Release();
	m_pHullShaderBlob->Release();
	m_pDomainShaderBlob->Release();
	m_pGeometryShaderBlob->Release();
	m_pPixelShaderBlob->Release();
	m_pErrorBlob->Release();

	m_pVertexShader->Release();
	m_pHullShader->Release();
	m_pDomainShader->Release();
	m_pGeometryShader->Release();
	m_pPixelShader->Release();
}

void Shader::CreateVertexShader(const std::wstring & param_wstrFilePath, const std::string & param_strFuncName, UINT param_uiHigh, UINT param_uiLow)
{
	// Shader 만들기
	UINT uiFlag = 0;

#ifdef _DEBUG
	uiFlag = D3DCOMPILE_DEBUG;
#endif

	std::wstring wstrPath = FilePathSearch::GetPath();
	wstrPath += param_wstrFilePath;

	char strTarget[20] = {};
	sprintf_s(strTarget, "vs_%d_%d", param_uiHigh, param_uiLow);

	D3DCompileFromFile(
		wstrPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		param_strFuncName.c_str(),
		strTarget, 
		uiFlag, 
		0, 
		&m_pVertexShaderBlob,
		&m_pErrorBlob
	);

	Device::GetInstance()->GetDevice()->CreateVertexShader(
		m_pVertexShaderBlob->GetBufferPointer(),
		m_pVertexShaderBlob->GetBufferSize(), 
		nullptr,
		&m_pVertexShader
	);

}

void Shader::CreatePixelShader(const std::wstring & param_wstrFilePath, const std::string & param_strFuncName, UINT param_uiHigh, UINT param_uiLow)
{
	// Shader 만들기
	UINT uiFlag = 0;

#ifdef _DEBUG
	uiFlag = D3DCOMPILE_DEBUG;
#endif

	std::wstring wstrPath = FilePathSearch::GetPath();
	wstrPath += param_wstrFilePath;

	char strTarget[20] = {};
	sprintf_s(strTarget, "ps_%d_%d", param_uiHigh, param_uiLow);

	// VtxShader Compile
	D3DCompileFromFile(
		wstrPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		param_strFuncName.c_str(), 
		strTarget, 
		uiFlag, 
		0, 
		&m_pPixelShaderBlob,
		&m_pErrorBlob
	);

	// Create Vertex Shader
	Device::GetInstance()->GetDevice()->CreatePixelShader(
		m_pPixelShaderBlob->GetBufferPointer(), 
		m_pPixelShaderBlob->GetBufferSize(),
		nullptr,
		&m_pPixelShader
	);

}

void Shader::UpdateData()
{
	Device::GetInstance()->GetContext()->VSSetShader(m_pVertexShader, nullptr, 0);
	Device::GetInstance()->GetContext()->HSSetShader(m_pHullShader, nullptr, 0);
	Device::GetInstance()->GetContext()->DSSetShader(m_pDomainShader, nullptr, 0);
	Device::GetInstance()->GetContext()->GSSetShader(m_pGeometryShader, nullptr, 0);
	Device::GetInstance()->GetContext()->PSSetShader(m_pPixelShader, nullptr, 0);
}
