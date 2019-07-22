#pragma once
class Core
{
private:
	HWND m_hWnd;
	TResolution m_tRes;

public:
	Core();
	~Core();

	int Init(HWND hWnd, bool bWindowed);
	void Progress();

	void Update();
	void Render();

	HWND GetWindowHwnd()
	{
		return m_hWnd;
	}

	static Core* GetInstance()
	{
		static Core instance;
		return &instance;
	}
};

