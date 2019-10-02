#pragma once
class CSaveLoadMgr
{
private:
	CSaveLoadMgr();
	~CSaveLoadMgr();

public:
	static void SaveScene(const wstring& _strPath);
	static void SaveResource(FILE* _pFile);

	static void LoadScene(const wstring& _strPath);
	static void LoadResource(FILE* _pFile);
};

