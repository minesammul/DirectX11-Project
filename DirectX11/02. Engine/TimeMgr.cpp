#include "stdafx.h"
#include "TimeMgr.h"

#include "Core.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llOldCount{}
	, m_llFrequency{}
	, m_fDeltaTime (0.f)
	, m_dAccTime(0.)
	, m_bFreeze(false)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llOldCount);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	
	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llOldCount.QuadPart) / (float)m_llFrequency.QuadPart;
	m_llOldCount = m_llCurCount;

	m_dAccTime += m_fDeltaTime;	

	if (m_bFreeze)
	{
		m_bFreeze = false;
		m_fDeltaTime = 1.f / 60.f;
	}

	if (m_dAccTime > 1.)
	{
		QueryPerformanceFrequency(&m_llFrequency);
		m_dAccTime = 0.;
		m_fFPS = 1 / (float)m_fDeltaTime;
	}

	g_global.fDeltaTime = DT;
	g_global.dAccTime = m_dAccTime;
}

void CTimeMgr::render(HDC _dc)
{	
	if (m_dAccTime > 1.)
	{
		QueryPerformanceFrequency(&m_llFrequency);
		m_dAccTime = 0.;
		m_fFPS = 1 / (float)m_fDeltaTime;
	}
	
	// ���ڿ� �׸��� �Լ�
	//wchar_t szCount[50] = L"";
	//_stprintf_s(szCount, L"FPS : %f, DT : %f", m_fFPS, m_fDeltaTime);
	//TextOut(_dc, 10, 10, szCount, wcslen(szCount));
}