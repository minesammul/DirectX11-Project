#include "stdafx.h"
#include "ResMgr.h"

#include "RenderMgr.h"
#include "Collider2D.h"
#include "Collider3D.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	CCollider2D::ClearMaterial();
	CCollider3D::ClearMaterial();

	// Clone 삭제
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Vec(m_vecCloneRes[i]);
	}

	// 원본 리소스 삭제
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Map(m_mapRes[i]);
	}
}

void CResMgr::init()
{
	CreateDefaultMesh();

	CreateDefaultShader();

	CreateDefaultMaterial();

	CreateDefaultFilter();

	InitSound();
}


void CResMgr::InitSound()
{
	FMOD::System_Create(&CSound::g_pFMOD);

	if (nullptr == CSound::g_pFMOD)
	{
		assert(nullptr);
	}

	CSound::g_pFMOD->init(32, FMOD_DEFAULT, nullptr);
}

void CResMgr::AddRes(RES_TYPE _eType, CResource * _pResource)
{
	map<wstring, CResource*>::iterator iter = m_mapRes[(UINT)_eType].find(_pResource->GetName());

	if (iter != m_mapRes[(UINT)_eType].end())
		return;

	m_mapRes[(UINT)_eType].insert(make_pair(_pResource->GetName(), _pResource));
}

CResPtr<CTexture> CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight
	, UINT _iBindFlag, D3D11_USAGE _eUsage, DXGI_FORMAT _eFormat)
{
	CResPtr<CTexture> pTex = FindRes<CTexture>(_strKey);
	assert(pTex == nullptr);

	pTex = new CTexture;
	pTex->Create(_iWidth, _iHeight, _iBindFlag, _eUsage, _eFormat);
	pTex->SetName(_strKey);

	m_mapRes[(UINT)RES_TYPE::TEXTURE].insert(make_pair(_strKey, pTex.GetPointer()));

	return pTex;
}

CResPtr<CTexture> CResMgr::CreateTexture(const wstring & _strKey, ID3D11Texture2D * _pTex2D)
{
	CResPtr<CTexture> pTex = FindRes<CTexture>(_strKey);
	assert(pTex == nullptr);

	pTex = new CTexture;
	pTex->Create(_pTex2D);
	pTex->SetName(_strKey);

	m_mapRes[(UINT)RES_TYPE::TEXTURE].insert(make_pair(_strKey, pTex.GetPointer()));

	return pTex;
}

CResPtr<CTexture> CResMgr::CreateArrayTexture(const wstring & _strKey, vector<CResPtr<CTexture>>& _vecTex)
{
	CResPtr<CTexture> pNewTex = new CTexture;
	pNewTex->CreateArrayTexture(_vecTex);
	pNewTex->SetName(_strKey);

	m_mapRes[(UINT)RES_TYPE::TEXTURE].insert(make_pair(_strKey, pNewTex.GetPointer()));

	return pNewTex;
}
