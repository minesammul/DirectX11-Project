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
	, m_bSave(true)
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetShader(CResPtr<CShader> _pShader)
{
	m_pShader = _pShader;
	//if (CCore::GetInst()->GetState() == SCENE_STATE::STOP)
	//{
	//	Save();
	//}
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
	case SHADER_PARAM::RWTEX_0:
	case SHADER_PARAM::RWTEX_1:
	case SHADER_PARAM::RWTEX_2:
	case SHADER_PARAM::RWTEX_3:
		iIdx = (UINT)_eType - (UINT)SHADER_PARAM::RWTEX_0;
		m_arrRWTex[iIdx] = *((CResPtr<CTexture>*)_pSrc);
		assert(nullptr != m_arrRWTex[iIdx]->GetUAV());
		break;
	default:
		assert(nullptr);
		break;
	}

	//if (CCore::GetInst()->GetState() == SCENE_STATE::STOP && m_bSave)
	//{
	//	Save();
	//}

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

	// Texture Update 하기
	UINT iCount = (UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0;
	for (UINT i = 0; i < iCount; ++i)
	{
		if (nullptr == m_arrTex[i])
		{
			CTexture::ClearRegister(i, (UINT)SHADER_TYPE::ALL_SHADER);
			m_param.arrTexCheck[i] = 0;
		}
		else
		{
			m_arrTex[i]->SetRegister(i, (UINT)SHADER_TYPE::ALL_SHADER);
			m_param.arrTexCheck[i] = 1;
		}
	}

	// RWTexture Update 하기
	iCount = (UINT)SHADER_PARAM::RWTEX_END - (UINT)SHADER_PARAM::RWTEX_0;
	for (UINT i = 0; i < iCount; ++i)
	{
		if (nullptr == m_arrRWTex[i])
		{
			CTexture::ClearRWRegister(i);
			m_param.arrRWTexCheck[i] = 0;
		}
		else
		{
			m_arrRWTex[i]->SetRWRegister(i);
			m_param.arrRWTexCheck[i] = 1;
		}
	}

	static CConstBuffer* pConstBuffer = CDevice::GetInst()->FindConstBuffer(L"ShaderParam");

	pConstBuffer->AddData(&m_param, sizeof(tShaderParam));
	pConstBuffer->UpdateData();
	pConstBuffer->SetRegisterAll();
}

void CMaterial::ExcuteComputeShader(UINT _x, UINT _y, UINT _z)
{
	CONTEXT->Dispatch(_x, _y, _z);
}

void CMaterial::Load(const wstring & _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	// Shader Key 읽기
	wstring strShaderName = LoadWString(pFile);
	m_pShader = CResMgr::GetInst()->FindRes<CShader>(strShaderName);

	// Shader Parameter 읽기
	fread(&m_param, sizeof(tShaderParam), 1, pFile);

	// Textrue Parameter 읽기
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
	errno_t err = _wfopen_s(&pFile, strFileName.c_str(), L"wb");

	if (pFile == nullptr)
		return;

	// Material 이 참조하고 있는 Shader 의 이름을 저장한다.
	wstring strKey;
	if (nullptr != m_pShader)
		strKey = m_pShader->GetName();

	SaveWString(strKey.c_str(), pFile);

	// Shader Parameter 저장
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

	// Texture 마감 데이터
	int iTexEnd = (UINT)SHADER_PARAM::TEX_END;
	fwrite(&iTexEnd, sizeof(int), 1, pFile);

	fclose(pFile);
}

bool CMaterial::LoadFromScene(FILE * _pFile)
{
	CResource::LoadFromScene(_pFile);

	// 키값, 경로
	CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(GetName());

	if (nullptr != pMtrl)
		return false;

	wstring strPath = CPathMgr::GetResPath();
	strPath += GetPath();

	Load(strPath);
}
