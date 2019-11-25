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
#include <Engine/MRT.h>

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
	SAFE_DELETE(m_pToolUICam);
	SAFE_DELETE(m_pGridObject);
	Safe_Delete_Vec(m_vecToolUI);

	SAFE_DELETE(m_pGridMtrl);
	SAFE_DELETE(m_pGridShader);
}


BEGIN_MESSAGE_MAP(CGameView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

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

void CGameView::CreateToolResource()
{
	// Tool Resource
	m_pGridShader = new CShader;

	m_pGridShader->CreateVertexShader(L"Shader\\tool.fx", "VS_Grid", 5, 0);
	m_pGridShader->CreatePixelShader(L"Shader\\tool.fx", "PS_Grid", 5, 0);
	m_pGridShader->SetBlendState(CRenderMgr::GetInst()->GetBlendState(BLEND_TYPE::ALPHABLEND));
	m_pGridShader->SetRSType(RS_TYPE::CULL_NONE);
	m_pGridShader->SetName(L"GridShader");

	m_pGridMtrl = new CMaterialEx;
	m_pGridMtrl->SetName(L"GridMtrl");
	m_pGridMtrl->SetShader(m_pGridShader);
}

void CGameView::CreateToolCamera()
{
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

	// Tool UI Camera
	m_pToolUICam = new CGameObjectEx;
	m_pToolUICam->AddComponent(new CTransform);
	m_pToolUICam->AddComponent(new CCameraEx);

	m_pToolUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	m_pToolUICam->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
}

void CGameView::CreateToolObject()
{
	tResolution res = CRenderMgr::GetInst()->GetResolution();

	// Grid Object
	m_pGridObject = new CGameObjectEx;

	m_pGridObject->AddComponent(new CTransform);
	m_pGridObject->AddComponent(new CMeshRender);
	m_pGridObject->AddComponent(new CGridScript);
	m_pGridObject->GetScript<CGridScript>()->SetToolCamera(m_pToolCam);

	m_pGridObject->Transform()->SetLocalScale(Vec3(100000.f, 100000.f, 1.f));
	m_pGridObject->Transform()->SetLocalRot(Vec3(XM_PI / 2.f, 0.f, 0.f));
	m_pGridObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	m_pGridObject->MeshRender()->SetMaterial(m_pGridMtrl);

	// Tool UI Object
	CGameObject* arrUI[5] = {};

	float fScale = 120.f;
	CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"TextureMtrl");
	CResPtr<CTexture> pTargetTex = nullptr;

	for (int i = 0; i < 5; ++i)
	{
		arrUI[i] = new CGameObjectEx;
		arrUI[i]->AddComponent(new CTransform);
		arrUI[i]->AddComponent(new CMeshRender);

		arrUI[i]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		arrUI[i]->MeshRender()->SetMaterial(pMtrl);

		arrUI[i]->Transform()->SetLocalScale(Vec3(fScale, fScale, 1.f));
		arrUI[i]->Transform()->SetLocalPos(Vec3((-res.fWidth / 2.f) + (fScale / 2.f) + (fScale * i)
			, (res.fHeight / 2.f) - (fScale / 2.f), 1.f));

		arrUI[i]->MeshRender()->GetCloneMaterial();

		m_vecToolUI.push_back(arrUI[i]);
	}

	pTargetTex = CResMgr::GetInst()->FindRes<CTexture>(L"DiffuseTargetTex");
	arrUI[0]->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTargetTex);

	pTargetTex = CResMgr::GetInst()->FindRes<CTexture>(L"NormalTargetTex");
	arrUI[1]->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTargetTex);

	pTargetTex = CResMgr::GetInst()->FindRes<CTexture>(L"PositionTargetTex");
	arrUI[2]->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTargetTex);

	pTargetTex = CResMgr::GetInst()->FindRes<CTexture>(L"LightTargetTex");
	arrUI[3]->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTargetTex);

	pTargetTex = CResMgr::GetInst()->FindRes<CTexture>(L"SpecularTargetTex");
	arrUI[4]->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pTargetTex);

}


void CGameView::init()
{
	CreateToolResource();
	CreateToolCamera();
	CreateToolObject();
}

void CGameView::update()
{
	SCENE_STATE eState = CCore::GetInst()->GetState();

	if (SCENE_STATE::PAUSE != eState && SCENE_STATE::STOP != eState)
		return;

	update_tool();

	render_tool();
}

void CGameView::update_tool()
{
	m_pToolCam->update();
	m_pToolCam->lateupdate();
	m_pToolCam->finalupdate();

	m_pToolUICam->update();
	m_pToolUICam->lateupdate();
	m_pToolUICam->finalupdate();

	// Tool 전용 Object update
	m_pGridObject->update();
	m_pGridObject->lateupdate();
	m_pGridObject->finalupdate();

	for (size_t i = 0; i < m_vecToolUI.size(); ++i)
	{
		m_vecToolUI[i]->update();
		m_vecToolUI[i]->lateupdate();
		m_vecToolUI[i]->finalupdate();
	}
}

void CGameView::render_tool()
{
	// Tool Camera Render	
	m_pToolCam->Camera()->render(); // deferred MRT 에 출력

	CRenderMgr::GetInst()->render_lights();

	// SwapChain MRT 로 복구
	CRenderMgr::GetInst()->GetMRT(MRT_TYPE::SWAPCHAIN)->OMSet();

	// Grid render
	m_pGridObject->render();

	// Tool UI render
	m_pToolUICam->Camera()->render();

	// Tool 전용 Object render
	for (size_t i = 0; i < m_vecToolUI.size(); ++i)
	{
		m_vecToolUI[i]->render();
	}

	CRenderMgr::GetInst()->Present();
}





// CGameView 메시지 처리기


void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
	GetClientRect(rt);

	CView::OnLButtonDown(nFlags, point);
}