#include "stdafx.h"
#include "TimeMgr.h"


TimeMgr::TimeMgr()
	: m_llCurCount{}
	, m_llOldCount{}
	, m_llFrequency{}
	, m_fDeltaTime (0.f)
	, m_fAccTime(0.f)
	, m_bFreeze(false)
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::Init()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llOldCount);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	
	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llOldCount.QuadPart) / (float)m_llFrequency.QuadPart;
	m_llOldCount = m_llCurCount;

	m_fAccTime += m_fDeltaTime;	

	if (m_bFreeze)
	{
		m_bFreeze = false;
		m_fDeltaTime = 1.f / 60.f;
	}
}

void TimeMgr::Render(HDC _dc)
{	
	if (m_fAccTime > 1.f)
	{
		QueryPerformanceFrequency(&m_llFrequency);
		m_fAccTime = 0.f;
		m_fFPS = 1 / m_fDeltaTime;
	}
	
	// 문자열 그리는 함수
	//wchar_t szCount[50] = L"";
	//_stprintf_s(szCount, L"FPS : %f, DT : %f", m_fFPS, m_fDeltaTime);
	//TextOut(_dc, 10, 10, szCount, wcslen(szCount));
}