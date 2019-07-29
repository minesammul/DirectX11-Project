#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "MeshRender.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Sound.h"
#include "Texture.h"
#include "PlayerScript.h"
#include "ResourceMgr.h"
#include "Prefab.h"
#include "BulletScript.h"

SceneMgr::SceneMgr()
	: m_pCurScene(nullptr)
	, m_pNextScene(nullptr)
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::CreatePrefab()
{
	GameObject* pBullet = new GameObject;

	Transform* pTransform = new Transform;
	MeshRender* pMeshRender = new MeshRender;

	pTransform->SetLocalScale(DirectX::XMFLOAT3(20.f, 20.f, 1.f));
	pTransform->SetLocalRot(DirectX::XMFLOAT3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(ResourceMgr::GetInstance()->FindRes<Mesh>(L"CircleMesh"));
	pMeshRender->SetShader(ResourceMgr::GetInstance()->FindRes<Shader>(L"DefaultShader"));

	pBullet->AddComponent(pTransform);
	pBullet->AddComponent(pMeshRender);
	pBullet->AddComponent(new BulletScript);

	BulletScript* pBulletScript = (BulletScript*)pBullet->GetScript<BulletScript>();
	pBulletScript->SetSpeed(500.f);

	ResourceMgr::GetInstance()->AddRes<Prefab>(L"BulletPrefab", new Prefab(pBullet));
}

void SceneMgr::RegisterCamera(Camera * _pCam)
{
	m_pCurScene->AddCamera(_pCam);
}

void SceneMgr::Init()
{
	// 수업용 임시 Scene 생성
	m_pCurScene = new Scene;

	// Layer 추가하기
	m_pCurScene->AddLayer(L"Default", 0);
	m_pCurScene->AddLayer(L"Player", 1);
	m_pCurScene->AddLayer(L"Bullet", 2);

	// Camera Object 만들기
	GameObject* pCamObj = new GameObject;
	pCamObj->AddComponent(new Transform);
	pCamObj->AddComponent(new Camera);

	pCamObj->GetCamera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->GetCamera()->SetFOV(DirectX::XM_PI / 4.f);
	pCamObj->GetCamera()->SetScale(1.f);

	pCamObj->GetCamera()->CheckLayer(m_pCurScene->FindLayer(L"Player")->GetLayerIdx());
	pCamObj->GetCamera()->CheckLayer(m_pCurScene->FindLayer(L"Bullet")->GetLayerIdx());

	m_pCurScene->AddObject(L"Default", pCamObj);


	GameObject* pObj = new GameObject;

	Transform* pTransform = new Transform;
	MeshRender* pMeshRender = new MeshRender;

	pTransform->SetLocalPos(DirectX::XMFLOAT3(0.f, 0.f, 500.f));
	pTransform->SetLocalScale(DirectX::XMFLOAT3(25.f, 25.f, 1.f));
	pTransform->SetLocalRot(DirectX::XMFLOAT3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(ResourceMgr::GetInstance()->FindRes<Mesh>(L"RectMesh"));
	pMeshRender->SetShader(ResourceMgr::GetInstance()->FindRes<Shader>(L"DefaultShader"));

	pObj->AddComponent(pTransform);
	pObj->AddComponent(pMeshRender);
	pObj->AddComponent(new PlayerScript);

	m_pCurScene->AddObject(L"Player", pObj);


	m_pCurScene->Awake();
	m_pCurScene->Start();

}

void SceneMgr::Progress()
{
	m_pCurScene->Update();
	m_pCurScene->LateUpdate();
	m_pCurScene->FinalUpdate();

}

void SceneMgr::Render()
{
	m_pCurScene->Render();

}
