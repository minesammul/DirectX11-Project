#pragma once
class FilePathSearch
{
private:
	static wchar_t m_cPath[255];

public:
	FilePathSearch();
	~FilePathSearch();

	static void Init();

	static wchar_t* GetPath()
	{
		return m_cPath;
	}
};

