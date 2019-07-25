#pragma once
#include "GameResource.h"

class Shader : public GameResource
{
private:
	ID3DBlob*				m_pVertexShaderBlob;
	ID3DBlob*				m_pHullShaderBlob;
	ID3DBlob*				m_pDomainShaderBlob;
	ID3DBlob*				m_pGeometryShaderBlob;
	ID3DBlob*				m_pPixelShaderBlob;
	ID3DBlob*				m_pErrorBlob;

	ID3D11VertexShader*		m_pVertexShader;
	ID3D11HullShader*		m_pHullShader;
	ID3D11DomainShader*		m_pDomainShader;
	ID3D11GeometryShader*	m_pGeometryShader;
	ID3D11PixelShader*		m_pPixelShader;

public:
	Shader();
	virtual ~Shader();

public:
	ID3DBlob* GetVertexShaderBlob() 
	{ 
		return  m_pVertexShaderBlob; 
	}

	ID3DBlob* GetHullShaderBlob() 
	{ 
		return m_pHullShaderBlob;
	}

	ID3DBlob* GetDomainShaderBlob() 
	{ 
		return m_pDomainShaderBlob; 
	}

	ID3DBlob* GetGeometryShaderBlob() 
	{ 
		return m_pGeometryShaderBlob;
	}

	ID3DBlob* GetPixelShaderBlob() 
	{ 
		return m_pPixelShaderBlob;
	}

	ID3D11VertexShader*	GetVertexShader()
	{
		return m_pVertexShader;
	}

	ID3D11HullShader* GetHullShader()
	{
		return m_pHullShader;
	}

	ID3D11DomainShader* GetDomainShader()
	{
		return m_pDomainShader;
	}

	ID3D11GeometryShader* GetGeometryShader()
	{
		return m_pGeometryShader;
	}

	ID3D11PixelShader* GetPixelShader()
	{
		return m_pPixelShader;
	}

	void CreateVertexShader(const std::wstring& param_wstrFilePath, const std::string& param_strFuncName, UINT param_uiHigh, UINT param_uiLow);
	//void CreateHullShader();
	//void CreateDomainShader();
	//void CreateGeometryShader();
	void CreatePixelShader(const std::wstring& param_wstrFilePath, const std::string& param_strFuncName, UINT param_uiHigh, UINT param_uiLow);

	void UpdateData();

};

