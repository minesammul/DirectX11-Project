#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"

#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"

#include "GameObject.h"

#include "MeshRender.h"
#include "Transform.h"
#include "Camera.h"
#include "Collider2D.h"
#include "Animator2D.h"

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Sound.h"
#include "Texture.h"
#include "Prefab.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_pNextScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	SAFE_DELETE(m_pCurScene);
	SAFE_DELETE(m_pNextScene);
}

void CSceneMgr::RegisterCamera(CCamera * _pCam)
{
	m_pCurScene->AddCamera(_pCam);
}

void CSceneMgr::init()
{
	// Resource Load
	//CreatePrefab();	
	
	//// 수업용 임시 Scene 생성
	m_pCurScene = new CScene;

	// Layer 추가하기
	m_pCurScene->AddLayer(L"Default", 0);	
}

void CSceneMgr::progress()
{
	m_pCurScene->update();
	m_pCurScene->lateupdate();

	m_pCurScene->finalupdate();

	CCollisionMgr::GetInst()->update();
	CEventMgr::GetInst()->update();
}

void CSceneMgr::progress_pause()
{
	m_pCurScene->finalupdate();
	CEventMgr::GetInst()->update();
}

void CSceneMgr::render()
{
	m_pCurScene->render();
}

void CSceneMgr::FindGameObject(const wstring & _strTagName, vector<CGameObject*>& _vecOut)
{
	m_pCurScene->FindGameObject(_strTagName, _vecOut);
}


void CSceneMgr::CreatePrefab()
{
	/*CGameObject* pBullet = new CGameObject;

	CTransform* pTransform = new CTransform;
	CMeshRender* pMeshRender = new CMeshRender;
		
	pTransform->SetLocalScale(Vec3(20.f, 20.f, 1.f));
	pTransform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh"));
	pMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"VtxColorMtrl"));

	pBullet->AddComponent(pTransform);
	pBullet->AddComponent(pMeshRender);
	pBullet->AddComponent(new CBulletScript);

	CBulletScript* pBulletScript = (CBulletScript*)pBullet->GetScript<CBulletScript>();
	pBulletScript->SetSpeed(500.f);
	
	CResMgr::GetInst()->AddRes<CPrefab>(L"BulletPrefab", new CPrefab(pBullet));*/
}