#include "stdafx.h"
#include "Material.h"

#include "Device.h"
#include "ConstBuffer.h"

CMaterial::CMaterial()
	: m_pShader(nullptr)
	, m_param{}
	, m_arrTex{}
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetData(SHADER_PARAM _eType, void * _pSrc)
{
	int iIdx = 0;

	switch (_eType)
	{
	case SHADER_PARAM::INT_0:		
	case SHADER_PARAM::INT_1:		
	case SHADER_PARAM::INT_2:		
	case SHADER_PARAM::INT_3:		
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::INT_0;
		m_param.arrInt[iIdx] = *((int*)_pSrc);
		break;
	case SHADER_PARAM::FLOAT_0:		
	case SHADER_PARAM::FLOAT_1:		
	case SHADER_PARAM::FLOAT_2:		
	case SHADER_PARAM::FLOAT_3:
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::FLOAT_0;
		m_param.arrFloat[iIdx] = *((float*)_pSrc);

		break;
	case SHADER_PARAM::VEC2_0:		
	case SHADER_PARAM::VEC2_1:		
	case SHADER_PARAM::VEC2_2:		
	case SHADER_PARAM::VEC2_3:
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::VEC2_0;
		m_param.arrVec2[iIdx] = *((Vec2*)_pSrc);
		break;
	case SHADER_PARAM::VEC4_0:		
	case SHADER_PARAM::VEC4_1:		
	case SHADER_PARAM::VEC4_2:		
	case SHADER_PARAM::VEC4_3:
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::VEC4_0;
		m_param.arrVec4[iIdx] = *((Vec4*)_pSrc);
		break;
	case SHADER_PARAM::MAT_0:		
	case SHADER_PARAM::MAT_1:		
	case SHADER_PARAM::MAT_2:		
	case SHADER_PARAM::MAT_3:
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::MAT_0;
		m_param.arrMat[iIdx] = *((Matrix*)_pSrc);
		break;
	case SHADER_PARAM::TEX_0:		
	case SHADER_PARAM::TEX_1:		
	case SHADER_PARAM::TEX_2:	
	case SHADER_PARAM::TEX_3:
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::TEX_0;
		m_arrTex[iIdx] = *((CResPtr<CTexture>*)_pSrc);
		break;
	default:
		assert(nullptr);
		break;
	}
}

void CMaterial::UpdateData()
{
	m_pShader->UpdateData();

	static CConstBuffer* pConstBuffer = CDevice::GetInst()->FindConstBuffer(L"ShaderParam");

	pConstBuffer->AddData(&m_param, sizeof(tShaderParam));	
	pConstBuffer->UpdateData();
	pConstBuffer->SetRegisterAll();

	// Texture Update го╠Б
	UINT iCount = (UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0;
	for (UINT i = 0; i < iCount; ++i)
	{
		if (nullptr == m_arrTex[i])
			continue;

		m_arrTex[i]->SetRegister(i, (UINT)SHADER_TYPE::PIXEL_SHADER);
		//m_arrTex[i]->SetRegisterAll(i);
	}	
}
