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
#include <Engine/RenderMgr.h>

#include "ToolCamScript.h"
#include "GridScript.h"
#include "MaterialEx.h"
// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)



CGameView::CGameView()
	: m_pToolCam(nullptr)
{

}

CGameView::~CGameView()
{
	SAFE_DELETE(m_pToolCam);
	Safe_Delete_Vec(m_vecToolObj);
	SAFE_DELETE(m_pGridMtrl);
	SAFE_DELETE(m_pGridShader);
}

BEGIN_MESSAGE_MAP(CGameView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CGameView::init()
{
	// Tool Resource
	m_pGridShader = new CShader;

	m_pGridShader->CreateVertexShader(L"Shader\\tool.fx", "VS_Grid", 5, 0);
	m_pGridShader->CreatePixelShader(L"Shader\\tool.fx", "PS_Grid", 5, 0);
	m_pGridShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	m_pGridShader->SetRSType(RS_TYPE::CULL_NONE);
	//m_pGridShader->AddParam(SHADER_PARAM::, L"");
	//m_pGridShader->AddParam(SHADER_PARAM::, L"");
	m_pGridShader->SetName(L"GridShader");

	m_pGridMtrl = new CMaterialEx;
	m_pGridMtrl->SetName(L"GridMtrl");
	m_pGridMtrl->SetShader(m_pGridShader);


	// Tool Camera
	m_pToolCam = new CGameObjectEx;

	m_pToolCam->AddComponent(new CTransform);
	m_pToolCam->AddComponent(new CCameraEx);
	m_pToolCam->AddComponent(new CToolCamScript);

	m_pToolCam->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));

	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_pToolCam->Camera()->CheckLayer(i);
	}

	// Tool Object
	// Grid Object
	CGameObject* pGridObj = new CGameObjectEx;

	pGridObj->AddComponent(new CTransform);
	pGridObj->AddComponent(new CMeshRender);
	pGridObj->AddComponent(new CGridScript);
	pGridObj->GetScript<CGridScript>()->SetToolCamera(m_pToolCam);

	pGridObj->Transform()->SetLocalScale(Vec3(100000.f, 100000.f, 1.f));
	pGridObj->Transform()->SetLocalRot(Vec3(XM_PI / 2.f, 0.f, 0.f));
	pGridObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pGridObj->MeshRender()->SetMaterial(m_pGridMtrl);


	m_vecToolObj.push_back(pGridObj);
}

void CGameView::update()
{
	SCENE_STATE eState = CCore::GetInst()->GetState();

	if (SCENE_STATE::PAUSE != eState && SCENE_STATE::STOP != eState)
		return;

	m_pToolCam->update();
	m_pToolCam->lateupdate();
	m_pToolCam->finalupdate();

	// Tool 전용 Object update
	for (size_t i = 0; i < m_vecToolObj.size(); ++i)
	{
		m_vecToolObj[i]->update();
		m_vecToolObj[i]->lateupdate();
		m_vecToolObj[i]->finalupdate();
	}

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

	// Tool 전용 Object render
	for (size_t i = 0; i < m_vecToolObj.size(); ++i)
	{
		m_vecToolObj[i]->render();
	}

	CRenderMgr::GetInst()->Present();
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
