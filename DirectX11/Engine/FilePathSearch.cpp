#include "stdafx.h"
#include "FilePathSearch.h"

wchar_t FilePathSearch::m_cPath[255] = {};

FilePathSearch::FilePathSearch()
{
}


FilePathSearch::~FilePathSearch()
{
}

void FilePathSearch::Init()
{
	GetCurrentDirectory(255, m_cPath);
	
	int iLen = wcslen(m_cPath);

	int iIndex = iLen - 1;
	while (iIndex > 0)
	{
		if (m_cPath[iIndex] == '\\')
		{
			wmemset(m_cPath + (iIndex + 1), 0, iLen - (iIndex + 1));
			break;
		}

		iIndex -= 1;
	}

	//wcscat_s(m_cPath , L"bin\\content\\");
}
