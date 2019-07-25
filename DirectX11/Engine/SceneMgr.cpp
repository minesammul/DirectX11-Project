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

SceneMgr::SceneMgr()
	: m_pCurScene(nullptr)
	, m_pNextScene(nullptr)
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Init()
{
	// ������ �ӽ� Scene ����
	m_pCurScene = new Scene;

	// Layer �߰��ϱ�
	m_pCurScene->AddLayer(L"Default", 0);
	m_pCurScene->AddLayer(L"Player", 1);

	// Camera Object �����
	//GameObject* pCamObj = new GameObject;
	//pCamObj->AddComponent(new Transform);
	//pCamObj->AddComponent(new Camera);

	//pCamObj->GetCamera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	//pCamObj->GetCamera()->SetFOV(DirectX::XM_PI / 4.f);
	//pCamObj->GetCamera()->SetScale(1.f);

	//m_pCurScene->AddObject(L"Default", pCamObj);

	// Object 3�� �����
	for (int i = 0; i < 3; ++i)
	{
		GameObject* pObj = new GameObject;

		Transform* pTransform = new Transform;
		MeshRender* pMeshRender = new MeshRender;

		pTransform->SetLocalPos(DirectX::XMFLOAT3(-200.f + i * 100.f, 0.f, 500.f));
		pTransform->SetLocalScale(DirectX::XMFLOAT3(25.f, 25.f, 1.f));
		pTransform->SetLocalRot(DirectX::XMFLOAT3(0.f, 0.f, 0.f));

		pMeshRender->SetMesh(ResourceMgr::GetInstance()->FindRes<Mesh>(L"CircleMesh"));
		pMeshRender->SetShader(ResourceMgr::GetInstance()->FindRes<Shader>(L"DefaultShader"));

		pObj->AddComponent(pTransform);
		pObj->AddComponent(pMeshRender);
		pObj->AddComponent(new PlayerScript);

		m_pCurScene->AddObject(L"Player", pObj);
	}

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
