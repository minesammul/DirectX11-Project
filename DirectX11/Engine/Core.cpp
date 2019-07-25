#include "stdafx.h"
#include "Core.h"

#include "Device.h"
#include "FilePathSearch.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"


Core::Core()
{
}


Core::~Core()
{
}

int Core::Init(HWND hWnd, bool bWindowed)
{
	m_hWnd = hWnd;

	RECT rt;
	GetClientRect(m_hWnd, &rt);

	m_tRes.fWidth = static_cast<float>(rt.right - rt.left);
	m_tRes.fHeight = static_cast<float>(rt.bottom - rt.top);
	
	if (FAILED(Device::GetInstance()->Init(hWnd, m_tRes, bWindowed)))
	{
		return E_FAIL;
	}

	KeyMgr::GetInstance()->Init();
	TimeMgr::GetInstance()->Init();
	FilePathSearch::Init();
	ResourceMgr::GetInstance()->Init();
	SceneMgr::GetInstance()->Init();

	Device::GetInstance()->CreateConstBuffer(L"Transform", sizeof(TTransform), 0);

	return S_OK;
}

void Core::Progress()
{
	KeyMgr::GetInstance()->Update();
	TimeMgr::GetInstance()->Update();


	SceneMgr::GetInstance()->Progress();

	// rendering
	// 장치 색상 초기화
	float arrCol[4] = { 0.f, 0.f, 0.f, 1.f };
	Device::GetInstance()->Clear(arrCol);

	// Scene Render
	SceneMgr::GetInstance()->Render();

	// 윈도우에 출력
	Device::GetInstance()->Present();
}
