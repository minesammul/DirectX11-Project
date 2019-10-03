#include "stdafx.h"
#include "Material.h"

#include "Device.h"
#include "ConstBuffer.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Core.h"

CMaterial::CMaterial()
	: m_pShader(nullptr)
	, m_param{}
	, m_arrTex{}
	, CResource(RES_TYPE::MATERIAL)
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetShader(CResPtr<CShader> _pShader)
{
	m_pShader = _pShader;
	if (CCore::GetInst()->GetState() == SCENE_STATE::STOP)
	{
		Save();
	}
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

	/*if (CCore::GetInst()->GetState() == SCENE_STATE::STOP)
	{
		Save();
	}*/
}

void CMaterial::UpdateData()
{
	if (m_pShader == nullptr)
	{
		return;
	}

	m_pShader->UpdateData();

	static CConstBuffer* pConstBuffer = CDevice::GetInst()->FindConstBuffer(L"ShaderParam");

	pConstBuffer->AddData(&m_param, sizeof(tShaderParam));	
	pConstBuffer->UpdateData();
	pConstBuffer->SetRegisterAll();

	// Texture Update �ϱ�
	UINT iCount = (UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0;
	for (UINT i = 0; i < iCount; ++i)
	{
		if (nullptr == m_arrTex[i])
			continue;

		m_arrTex[i]->SetRegister(i, (UINT)SHADER_TYPE::PIXEL_SHADER);
		//m_arrTex[i]->SetRegisterAll(i);
	}	
}

void CMaterial::Load(const wstring & _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	// Shader Key �б�
	wstring strShaderName = LoadWString(pFile);
	m_pShader = CResMgr::GetInst()->FindRes<CShader>(strShaderName);

	// Shader Parameter �б�
	fread(&m_param, sizeof(tShaderParam), 1, pFile);

	// Textrue Parameter �б�
	while (true)
	{
		int index = 0;
		fread(&index, sizeof(int), 1, pFile);

		if (index == (UINT)SHADER_PARAM::TEX_END)
			break;

		wstring strKey = LoadWString(pFile);
		wstring strPath = LoadWString(pFile);

		m_arrTex[index] = CResMgr::GetInst()->FindRes<CTexture>(strKey);
		if (nullptr == m_arrTex[index])
		{
			m_arrTex[index] = CResMgr::GetInst()->Load<CTexture>(strKey, strPath);
		}
	}


	fclose(pFile);
}

void CMaterial::Save()
{
	wstring strFileName = CPathMgr::GetResPath();
	strFileName += L"Material\\";
	strFileName += GetName();
	strFileName += L".mtrl";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFileName.c_str(), L"wb");

	// Material �� �����ϰ� �ִ� Shader �� �̸��� �����Ѵ�.
	wstring strKey;
	if (nullptr != m_pShader)
		strKey = m_pShader->GetName();

	SaveWString(strKey.c_str(), pFile);

	// Shader Parameter ����
	fwrite(&m_param, sizeof(tShaderParam), 1, pFile);

	// Shader Parameter Texture 
	for (UINT i = 0; i < (UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0; ++i)
	{
		if (nullptr != m_arrTex[i])
		{
			fwrite(&i, sizeof(int), 1, pFile);
			SaveWString(m_arrTex[i]->GetName().c_str(), pFile);
			SaveWString(m_arrTex[i]->GetPath().c_str(), pFile);
		}
	}

	// Texture ���� ������
	int iTexEnd = (UINT)SHADER_PARAM::TEX_END;
	fwrite(&iTexEnd, sizeof(int), 1, pFile);

	fclose(pFile);
}

bool CMaterial::LoadFromScene(FILE * _pFile)
{
	CResource::LoadFromScene(_pFile);

	// Ű��, ���
	CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(GetName());

	if (nullptr != pMtrl)
		return false;

	wstring strPath = CPathMgr::GetResPath();
	strPath += GetPath();

	Load(strPath);
}