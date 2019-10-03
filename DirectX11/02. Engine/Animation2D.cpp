#include "stdafx.h"
#include "Animation2D.h"

#include "Device.h"
#include "ConstBuffer.h"

#include "TimeMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"

tAnim2D g_anim2d;

CAnimation2D::CAnimation2D()
	: m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation2D::~CAnimation2D()
{
}

void CAnimation2D::Play()
{
	if (m_bFinish)
	{
		m_iCurFrm = 0;
		m_bFinish = false;
	}

	m_bPlay = true;
}




void CAnimation2D::SetNowFrameOffset(Vec2 offset)
{
	//SetName(_strName);
	Vec2 beforeOffsetUV = Vec2(m_vecFrm[m_iCurFrm].LTOffset.x / m_vecFrm[m_iCurFrm].pTex->GetWidth(), m_vecFrm[m_iCurFrm].LTOffset.y / m_vecFrm[m_iCurFrm].pTex->GetHeight());
	Vec2 offsetUV = Vec2(offset.x / m_vecFrm[m_iCurFrm].pTex->GetWidth(), offset.y / m_vecFrm[m_iCurFrm].pTex->GetHeight());
	
	offsetUV.x -= beforeOffsetUV.x;
	offsetUV.y -= beforeOffsetUV.y;

	m_vecFrm[m_iCurFrm].LTOffset = offset;

	m_vecFrm[m_iCurFrm].vLT.x += offsetUV.x;
	m_vecFrm[m_iCurFrm].vLT.y += offsetUV.y;
	//float fWidth = _pTex->GetWidth();
	//float fHeight = _pTex->GetHeight();

	//tAnim2DFrm tFrm = {};

	//Vec2 vCropUV = Vec2(_vCropSize.x / fWidth, _vCropSize.y / fHeight);
	//Vec2 vLTUV = Vec2((_vLT.x + offset.x) / fWidth, (_vLT.y + offset.y) / fHeight);
	//Vec2 offsetUV = Vec2(offset.x / fWidth, offset.y / fHeight);

	//for (int i = 0; i < _iFrmCount; ++i)
	//{
	//	tFrm.vLT = vLTUV;
	//	tFrm.vLT.x += (i * (vCropUV.x + 2 * offsetUV.x));
	//	//tFrm.vLT.x += (i * vLTUV.x);

	//	tFrm.vSize = vCropUV;
	//	tFrm.vTerm = _fTerm;
	//	tFrm.pTex = _pTex;

	//	tFrm.LTOffset.x = offset.x;
	//	tFrm.LTOffset.y = offset.y;

	//	m_vecFrm.push_back(tFrm);
	//}

}

void CAnimation2D::update()
{		
}

void CAnimation2D::lateupdate()
{
}

void CAnimation2D::finalupdate()
{
	if (!m_bPlay)
		return;

	m_fAccTime += DT;

	if (m_vecFrm[m_iCurFrm].vTerm < m_fAccTime)
	{
		float fDiff = m_fAccTime - m_vecFrm[m_iCurFrm].vTerm;
		
		UINT iNextFrm = m_iCurFrm + 1;

		if (iNextFrm >= m_vecFrm.size())
		{
			iNextFrm = m_vecFrm.size() - 1; // ������ ������ ����
			m_fAccTime = 0.f;
			m_bFinish = true;
			m_bPlay = false;
		}
		else
		{
			while (true)
			{
				fDiff -= m_vecFrm[iNextFrm].vTerm;
				if (fDiff < 0.f)
				{
					m_fAccTime = m_vecFrm[iNextFrm].vTerm + fDiff;
					break;
				}

				++iNextFrm;
				if (m_vecFrm.size() <= iNextFrm) // Animation ����
				{
					iNextFrm = m_vecFrm.size() - 1; // ������ ������ ����
					m_fAccTime = 0.f;
					m_bFinish = true;
					m_bPlay = false;
					break;
				}
			}
		}		

		m_iCurFrm = iNextFrm;
	}
}

void CAnimation2D::UpdateData()
{	
	static CConstBuffer* pCB = CDevice::GetInst()->FindConstBuffer(L"Anim2D");

	g_anim2d.iAnimCheck = 1;
	g_anim2d.vLT = m_vecFrm[m_iCurFrm].vLT;
	g_anim2d.vSize = m_vecFrm[m_iCurFrm].vSize;

	pCB->AddData(&g_anim2d, sizeof(tAnim2D));
	pCB->UpdateData();
	pCB->SetRegister((UINT)SHADER_TYPE::PIXEL_SHADER);

	m_vecFrm[m_iCurFrm].pTex->SetRegister(17, (UINT)SHADER_TYPE::PIXEL_SHADER);
}

void CAnimation2D::Create(const wstring & _strName
	, CResPtr<CTexture> _pTex, Vec2 _vLT, Vec2 _vCropSize
	, int _iFrmCount, float _fTerm)
{
	SetName(_strName);
	
	float fWidth = _pTex->GetWidth();
	float fHeight = _pTex->GetHeight();

	tAnim2DFrm tFrm = {};

	Vec2 vCropUV = Vec2(_vCropSize.x / fWidth, _vCropSize.y / fHeight);
	Vec2 vLTUV = Vec2(_vLT.x / fWidth, _vLT.y / fHeight);

	for (int i = 0; i < _iFrmCount; ++i)
	{
		tFrm.vLT = vLTUV;
		tFrm.vLT.x += (i * vCropUV.x);

		tFrm.vSize = vCropUV;
		tFrm.vTerm = _fTerm;
		tFrm.pTex = _pTex;

		tFrm.LTOffset.x = 0.0f;
		tFrm.LTOffset.y = 0.0f;

		m_vecFrm.push_back(tFrm);
	}
}

void CAnimation2D::Create(const wstring & _strName, CResPtr<CTexture> _pTex, Vec2 _vLT, Vec2 _vCropSize, Vec2 offset, int _iFrmCount, float _fTerm)
{
	SetName(_strName);

	float fWidth = _pTex->GetWidth();
	float fHeight = _pTex->GetHeight();

	tAnim2DFrm tFrm = {};

	Vec2 vCropUV = Vec2(_vCropSize.x / fWidth, _vCropSize.y / fHeight);
	Vec2 vLTUV = Vec2((_vLT.x + offset.x) / fWidth, (_vLT.y + offset.y) / fHeight);
	Vec2 offsetUV = Vec2(offset.x / fWidth, offset.y / fHeight);

	for (int i = 0; i < _iFrmCount; ++i)
	{
		tFrm.vLT = vLTUV;
		tFrm.vLT.x += (i * (vCropUV.x + 2*offsetUV.x));
		//tFrm.vLT.x += (i * vLTUV.x);

		tFrm.vSize = vCropUV;
		tFrm.vTerm = _fTerm;
		tFrm.pTex = _pTex;

		tFrm.LTOffset.x = offset.x;
		tFrm.LTOffset.y = offset.y;

		m_vecFrm.push_back(tFrm);
	}
}

void CAnimation2D::Create(const wstring & _strName, const wstring & _strFolderPath, float _fTerm)
{
	SetName(_strName);

	wstring strFolderPath = CPathMgr::GetResPath();
	strFolderPath += _strFolderPath;
	strFolderPath += L"\\*.*";

	WIN32_FIND_DATA tData = {};
	HANDLE h = (HANDLE)FindFirstFile(strFolderPath.c_str(), &tData);
	UINT err = GetLastError();
	CResPtr<CTexture> pTex = nullptr;

	tAnim2DFrm tFrm = {};

	while (true)
	{		
		const wchar_t* pExt = CPathMgr::GetExt(tData.cFileName);

		if (!wcscmp(pExt, L".png") 
			|| !wcscmp(pExt, L".bmp") 
			|| !wcscmp(pExt, L".jpg") 
			|| !wcscmp(pExt, L".jpeg"))
		{			
			wstring strKey = _strFolderPath + tData.cFileName;

			pTex = CResMgr::GetInst()->Load<CTexture>(strKey, strKey);
			tFrm.pTex = pTex;
			tFrm.vTerm = _fTerm;
			tFrm.vLT = Vec2(0.f, 0.f);
			tFrm.vSize = Vec2(1.f, 1.f);

			tFrm.LTOffset.x = 0.0f;
			tFrm.LTOffset.y = 0.0f;

			m_vecFrm.push_back(tFrm);
		}

		if (false == FindNextFile(h, &tData))
		{
			err = GetLastError();
			break;
		}
	}
}

void CAnimation2D::ClearRegister()
{
	static CConstBuffer* pCB = CDevice::GetInst()->FindConstBuffer(L"Anim2D");

	g_anim2d.iAnimCheck = 0;
	g_anim2d.vLT = Vec2();
	g_anim2d.vSize = Vec2();

	pCB->AddData(&g_anim2d, sizeof(tAnim2D));
	pCB->UpdateData();
	pCB->SetRegister((UINT)SHADER_TYPE::PIXEL_SHADER);

	CTexture::ClearRegister(17, (UINT)SHADER_TYPE::PIXEL_SHADER);
}