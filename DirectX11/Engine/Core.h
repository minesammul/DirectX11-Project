#pragma once
class Core
{
private:
	HWND m_hWnd;
	TResolution m_tRes;

public:
	Core();
	~Core();

public:
	int Init(HWND hWnd, bool bWindowed);
	void Progress();

	HWND GetWindowHwnd()
	{
		return m_hWnd;
	}

	TResolution GetResolution()
	{
		return m_tRes;
	}

	static Core* GetInstance()
	{
		static Core instance;
		return &instance;
	}
};

