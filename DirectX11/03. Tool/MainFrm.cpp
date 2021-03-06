﻿
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "ToolApp.h"

#include "MainFrm.h"
#include "GameView.h"
#include "HierachyView.h"
#include "ComponentView.h"
#include "BtnView.h"
#include "DbgView.h"
#include "ResourceDlg.h"
#include "GameObjectDlg.h"

#include <ResMgr.h>
#include <Material.h>
#include <SaveLoadMgr.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneMgr.h>
#include <Transform.h>
#include <MeshRender.h>
#include <Animator2D.h>
#include <Collider2D.h>
#include <Collider3D.h>
#include <KeyMgr.h>
#include <Core.h>
#include <Script.h>
#include <Terrain.h>
#include <Light3D.h>
#include <ParticleSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_RESOURCE_NEWMATERIAL, &CMainFrame::OnResourceNewmaterialCreate)
	ON_COMMAND(ID_32773, &CMainFrame::OnSaveScene)
	ON_COMMAND(ID_32774, &CMainFrame::OnLoadScene)
	ON_COMMAND(ID_GAMEOBJECT_2DRECT, &CMainFrame::OnGameobject2drect)
	ON_COMMAND(ID_GAMEOBJECT_CREATETERRAIN, &CMainFrame::OnGameObjectCreateTerrain)
	ON_COMMAND(ID_GAMEOBJECT_CREATE3DCUBE, &CMainFrame::OnGameobjectCreate3dcube)
	ON_COMMAND(ID_GAMEOBJECT_CREATEEMPTYOBJECT, &CMainFrame::OnGameobjectCreateEmptyObject)
	ON_COMMAND(ID_GAMEOBJECT_CREATEFBXOBJECT, &CMainFrame::OnGameobjectCreatefbxobject)
	ON_COMMAND(ID_REFRESHDLG_REFRESHGAMEOBJECTDLG, &CMainFrame::OnRefreshdlgRefreshgameobjectdlg)
	ON_COMMAND(ID_GAMEOBJECT_CREATEPARTICLE, &CMainFrame::OnGameobjectCreateparticle)
	ON_COMMAND(ID_GAMEOBJECT_CREATEPOINTLIGHT, &CMainFrame::OnGameobjectCreatepointlight)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	RECT rt = {};
	GetWindowRect(&rt);
	SetWindowPos(nullptr, 50, 25, rt.right - rt.left, rt.bottom - rt.top, 0);
	   
	// SplitterWnd 를 이용해서 작업영역을 분할
	m_mainSplitter.SetBorder(POINT{ 0, 0 }, POINT{ 1, 1 });
	m_mainSplitter.CreateStatic(this, 1, 3); // (0, 0)   (0, 1)   (0, 2)	

	m_mainSplitter.SetColumnInfo(0, GAMEVIEW_X - 4, GAMEVIEW_X - 4);
	m_mainSplitter.SetColumnInfo(1, HIERACHYVIEW_X, HIERACHYVIEW_X);
		
	m_mainSplitter.CreateView(0, 1, RUNTIME_CLASS(CHierachyView), CSize(HIERACHYVIEW_X, FRAME_Y), nullptr);
	m_mainSplitter.CreateView(0, 2, RUNTIME_CLASS(CComponentView),  CSize(COMVIEW_X, FRAME_Y), nullptr);

	// MainSplitter 의 1열을 다시 3행으로 분할한다.
	m_subSplitter.CreateStatic(&m_mainSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_mainSplitter.IdFromRowCol(0, 0));
	m_subSplitter.SetBorder(POINT{ 0, 0 }, POINT{ 1, 1 });
	m_subSplitter.CreateView(0, 0, RUNTIME_CLASS(CBtnView), CSize(BTNVIEW_X, BTNVIEW_Y), nullptr);
	m_subSplitter.CreateView(1, 0, RUNTIME_CLASS(CGameView), CSize(GAMEVIEW_X, GAMEVIEW_Y), nullptr);
	m_subSplitter.CreateView(2, 0, RUNTIME_CLASS(CDbgView), CSize(DBGVIEW_X, DBGVIEW_Y), nullptr);
	
	return 0;
}

void CMainFrame::init()
{
	// Init
	((CGameView*)GetGameView())->init();
	((CComponentView*)GetComView())->init();
	((CHierachyView*)GetHierachyView())->init();

	// GameView Forcus
	::SetFocus(GetGameView()->m_hWnd);
}

void CMainFrame::update()
{
	// CompnentView update
	((CComponentView*)GetComView())->update();
	((CGameView*)GetGameView())->update();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
		
	RECT rt = {0, 0, FRAME_X, FRAME_Y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	
	cs.cx = rt.right - rt.left;
	cs.cy = rt.bottom - rt.top;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnResourceNewmaterialCreate()
{
	CResPtr<CMaterial> pMtrl = new CMaterial;

	CString strKey = L"New Material";

	CResPtr<CMaterial> pFindMtrl = nullptr;
	int i = 0;
	while (true)
	{
		pFindMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strKey.GetBuffer());

		if (nullptr == pFindMtrl)
		{
			CResMgr::GetInst()->AddRes(strKey.GetBuffer(), pMtrl);
			break;
		}
		else
		{
			++i;
			strKey.Format(L"New Material %d", i);
		}
	}

	CHierachyView* pView = (CHierachyView*)GetHierachyView();
	pView->GetResDlg()->Renew();

	//pMtrl->Save();
}


void CMainFrame::OnSaveScene()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	static wchar_t szFilter[] = L"Scene 파일(*.scene)|*.scene|모든파일(*.*)|*.*||";

	CFileDialog dlg(FALSE, nullptr, nullptr, OFN_HIDEREADONLY, szFilter);

	CString strInitPath = CPathMgr::GetResPath();
	strInitPath += L"Scene\\";
	dlg.m_ofn.lpstrInitialDir = strInitPath;

	CString pathName;
	INT_PTR clickResult = dlg.DoModal();
	if (IDOK == clickResult)
	{
		pathName = dlg.GetPathName();
	}
	else if (IDCANCEL == clickResult)
	{
		return;
	}

	CSaveLoadMgr::SaveScene(pathName.GetBuffer());
}


void CMainFrame::OnLoadScene()
{
	static wchar_t szFilter[] = L"Scene 파일(*.scene)|*.scene|모든파일(*.*)|*.*||";

	CFileDialog dlg(TRUE, nullptr, nullptr, OFN_HIDEREADONLY, szFilter);

	CString strInitPath = CPathMgr::GetResPath();
	strInitPath += L"Scene\\";
	dlg.m_ofn.lpstrInitialDir = strInitPath;

	CString pathName;
	INT_PTR clickResult = dlg.DoModal();
	if (IDOK == clickResult)
	{
		pathName = dlg.GetPathName();
	}
	else if (IDCANCEL == clickResult)
	{
		return;
	}

	CCore::GetInst()->SetState(SCENE_STATE::LOAD);

	CSaveLoadMgr::LoadScene(pathName.GetBuffer());

	((CGameView*)GetGameView())->DeleteResource();
	((CGameView*)GetGameView())->init();

	// GameObject 트리컨트롤 목록 갱신
	CGameObjectDlg* ObjectDlg = ((CHierachyView*)GetHierachyView())->GetObjectDlg();
	ObjectDlg->init();

	// ResDlg 트리컨트롤 리소스 목록 갱신
	ResourceDlg* pResDlg = ((CHierachyView*)GetHierachyView())->GetResDlg();
	pResDlg->Renew();

	((CComponentView*)GetComView())->SetTarget(nullptr);

	for (int index = 0; index < MAX_LAYER; index++)
	{
		CLayer* curLayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(index);
		if (curLayer == nullptr)
		{
			continue;
		}

		vector<CGameObject*> layerAllObject = CSceneMgr::GetInst()->GetCurScene()->GetLayer(index)->GetParentObject();
		for (int objectIndex = 0; objectIndex < layerAllObject.size(); objectIndex++)
		{
			CGameObject* object = layerAllObject[objectIndex];
			if (object->Terrain() != nullptr)
			{
				CGameObject* pToolCamObj = ((CGameView*)GetGameView())->GetToolCamera();
				object->Terrain()->SetCamera(pToolCamObj->Camera());
			}
		}
	}

	CCore::GetInst()->SetState(SCENE_STATE::STOP);
}


void CMainFrame::OnGameobject2drect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CGameObject* newObject = new CGameObject;

	CString newObjectName;
	int newObjectNumber = 0;
	while (true)
	{
		newObjectName.Format(L"2DRect_%d", newObjectNumber);
		if (pCurScene->IsExistGameObjectName(newObjectName.GetBuffer()) == true)
		{
			newObjectNumber++;
		}
		else
		{
			break;
		}
	}

	newObject->SetName(newObjectName.GetBuffer());

	CTransform* pTransform = new CTransform;
	CMeshRender* pMeshRender = new CMeshRender;
	CCollider2D* pCollider2D = new CCollider2D;

	pTransform->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pTransform->SetLocalScale(Vec3(100.f, 100.f, 1.f));
	pTransform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	newObject->AddComponent(pTransform);
	newObject->AddComponent(pMeshRender);
	newObject->AddComponent(pCollider2D);

	pCurScene->AddObject(L"Default", newObject);

	((CHierachyView*)GetHierachyView())->init_object();
}


void CMainFrame::OnGameObjectCreateTerrain()
{
	CGameObject* pNewObj = new CGameObject;
	pNewObj->SetName(L"Terrain");
	pNewObj->AddComponent(new CTransform);
	pNewObj->AddComponent(new CMeshRender);
	pNewObj->AddComponent(new CTerrain);

	pNewObj->Terrain()->init(64, 64);

	CGameObject* pToolCamObj = ((CGameView*)GetGameView())->GetToolCamera();
	pNewObj->Terrain()->SetCamera(pToolCamObj->Camera());

	CSceneMgr::GetInst()->GetCurScene()->AddObject(L"Default", pNewObj);

	((CHierachyView*)GetHierachyView())->init_object();
}


void CMainFrame::OnGameobjectCreate3dcube()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CGameObject* newObject = new CGameObject;

	CString newObjectName;
	int newObjectNumber = 0;
	while (true)
	{
		newObjectName.Format(L"3DCube_%d", newObjectNumber);
		if (pCurScene->IsExistGameObjectName(newObjectName.GetBuffer()) == true)
		{
			newObjectNumber++;
		}
		else
		{
			break;
		}
	}

	newObject->SetName(newObjectName.GetBuffer());

	CTransform* pTransform = new CTransform;
	CMeshRender* pMeshRender = new CMeshRender;

	pTransform->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pTransform->SetLocalScale(Vec3(100.f, 100.f, 100.f));
	pTransform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
	pMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"));

	newObject->AddComponent(pTransform);
	newObject->AddComponent(pMeshRender);

	pCurScene->AddObject(L"Default", newObject);

	((CHierachyView*)GetHierachyView())->init_object();
}


void CMainFrame::OnGameobjectCreateEmptyObject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CGameObject* newObject = new CGameObject;

	CString newObjectName;
	int newObjectNumber = 0;
	while (true)
	{
		newObjectName.Format(L"EmptyObject_%d", newObjectNumber);
		if (pCurScene->IsExistGameObjectName(newObjectName.GetBuffer()) == true)
		{
			newObjectNumber++;
		}
		else
		{
			break;
		}
	}

	newObject->SetName(newObjectName.GetBuffer());

	CTransform* pTransform = new CTransform;

	pTransform->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pTransform->SetLocalScale(Vec3(100.f, 100.f, 100.f));
	pTransform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	newObject->AddComponent(pTransform);

	pCurScene->AddObject(L"Default", newObject);

	((CHierachyView*)GetHierachyView())->init_object();
}


void CMainFrame::OnGameobjectCreatefbxobject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnRefreshdlgRefreshgameobjectdlg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	((CHierachyView*)GetHierachyView())->init_object();
}


void CMainFrame::OnGameobjectCreateparticle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	CString newObjectName;
	int newObjectNumber = 0;
	while (true)
	{
		newObjectName.Format(L"Particle_%d", newObjectNumber);
		if (pCurScene->IsExistGameObjectName(newObjectName.GetBuffer()) == true)
		{
			newObjectNumber++;
		}
		else
		{
			break;
		}
	}

	CGameObject* pParticle = new CGameObject;
	pParticle->SetName(newObjectName.GetBuffer());
	pParticle->AddComponent(new CTransform);
	pParticle->AddComponent(new CParticleSystem);

	pParticle->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));

	
	pCurScene->AddObject(L"Default", pParticle);
}


void CMainFrame::OnGameobjectCreatepointlight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"PointLight1");
	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light3D()->SetLightDir(Vec3(1.f, -1.f, 1.f));
	pLightObj->Light3D()->SetLightDiffuse(Vec3(0.8f, 0.8f, 0.8f));
	pLightObj->Light3D()->SetLightSpecular(Vec3(0.3f, 0.3f, 0.3f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.1f, 0.1f, 0.1f));
	pLightObj->Light3D()->SetLightRange(100.f);

	pCurScene->AddObject(L"Default", pLightObj);

}
