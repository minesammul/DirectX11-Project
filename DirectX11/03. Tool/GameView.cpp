// GameView.cpp: 구현 파일
//

#include "stdafx.h"
#include "GameView.h"
#include "MainFrm.h"
#include "ComponentView.h"
#include <SceneMgr.h>

#include "GameObjectEx.h"
#include "CameraEx.h"

#include <Engine/Transform.h>
#include <Engine/SceneMgr.h>
#include <Engine/Scene.h>
#include <Engine/Layer.h>
#include <Engine/Device.h>
#include <Engine/Core.h>

#include "ToolCamScript.h"

// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)



CGameView::CGameView()
	: m_pToolCam(nullptr)
{

}

CGameView::~CGameView()
{
	SAFE_DELETE(m_pToolCam);
}

BEGIN_MESSAGE_MAP(CGameView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CGameView::init()
{
	m_pToolCam = new CGameObjectEx;

	m_pToolCam->AddComponent(new CTransform);
	m_pToolCam->AddComponent(new CCameraEx);
	m_pToolCam->AddComponent(new CToolCamScript);

	m_pToolCam->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));

	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_pToolCam->Camera()->CheckLayer(i);
	}

}

void CGameView::update()
{
	SCENE_STATE eState = CCore::GetInst()->GetState();

	if (SCENE_STATE::PAUSE != eState && SCENE_STATE::STOP != eState)
		return;

	m_pToolCam->update();
	m_pToolCam->lateupdate();
	m_pToolCam->finalupdate();

	g_transform.matView = m_pToolCam->Camera()->GetViewMat();
	g_transform.matProj = m_pToolCam->Camera()->GetProjMat();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == pCurScene->GetLayer(i))
			continue;

		if (m_pToolCam->Camera()->IsValiedLayer(i))
			pCurScene->GetLayer(i)->render();
	}

	CDevice::GetInst()->Present();

}

// CGameView 그리기

void CGameView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CGameView 진단

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGameView 메시지 처리기


void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	POINT mousePoint;
	mousePoint.x = point.x;
	mousePoint.y = point.y;

	CComponentView* pComView = (CComponentView*)((CMainFrame*)AfxGetMainWnd())->GetComView();

	pComView->SetTarget(CSceneMgr::GetInst()->MousePicking(mousePoint));

	CView::OnLButtonDown(nFlags, point);
}
