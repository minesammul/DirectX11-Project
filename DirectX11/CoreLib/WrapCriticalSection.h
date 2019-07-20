#pragma once

class WrapCriticalSection
{
private:
	CRITICAL_SECTION m_criticalSection;

public:
	WrapCriticalSection()
	{
		InitializeCriticalSection(&m_criticalSection);
	}

	~WrapCriticalSection()
	{
		DeleteCriticalSection(&m_criticalSection);
	}

	CRITICAL_SECTION GetCriticalSection()
	{
		return m_criticalSection;
	}
};

class WrapCriticalSectionLock
{
private:
	WrapCriticalSection m_wrapCriticalSection;

public:
	WrapCriticalSectionLock()
	{
		EnterCriticalSection(&m_wrapCriticalSection.GetCriticalSection());
	}

	~WrapCriticalSectionLock()
	{
		LeaveCriticalSection(&m_wrapCriticalSection.GetCriticalSection());
	}
};