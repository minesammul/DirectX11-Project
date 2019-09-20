#pragma once

class CRenderMgr;
class CSceneMgr;

class CCore
{
	SINGLE(CCore);
private:
	HWND			m_hWnd;	// 출력 윈도우 핸들
	tResolution		m_tRes; // 윈도우 해상도 정보
	
	void(CRenderMgr::*render)(void);
	void(CSceneMgr::*scene_progress)(void);

public:
	int init(HWND _hWnd, bool _bWindowed);
	void progress();

	void SetRenderMode(bool _bTool);
	void Play(bool _bTrue);


public:
	HWND GetWindowHwnd() { return m_hWnd; }
};

