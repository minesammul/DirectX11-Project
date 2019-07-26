#include "stdafx.h"
#include "PlayerScript.h"

#include "BulletScript.h"


PlayerScript::PlayerScript()
{
}


PlayerScript::~PlayerScript()
{
}

void PlayerScript::Update()
{
	GameObject* pObj = Object();

	DirectX::XMFLOAT3 vPos = pObj->GetTransform()->GetLocalPos();

	// 키입력으로 삼각형 움직이기
	if (KEYHOLD(KEY_TYPE::KEY_LEFT))
	{
		//g_vWorldPos.x -= 100.f * DT;
		vPos.x -= 100.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_RIGHT))
	{
		//g_vWorldPos.x += 100.f * DT;
		vPos.x += 100.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_UP))
	{
		vPos.y += 100.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_DOWN))
	{
		vPos.y -= 100.f * DT;
	}

	pObj->GetTransform()->SetLocalPos(vPos);

	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		CreateBullet();
	}
}

void PlayerScript::CreateBullet()
{
	GameObject* pBullet = new GameObject;

	Transform* pTransform = new Transform;
	MeshRender* pMeshRender = new MeshRender;

	pTransform->SetLocalPos(GetTransform()->GetLocalPos());
	pTransform->SetLocalScale(DirectX::XMFLOAT3(20.f, 20.f, 1.f));
	pTransform->SetLocalRot(DirectX::XMFLOAT3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(ResourceMgr::GetInstance()->FindRes<Mesh>(L"CircleMesh"));
	pMeshRender->SetShader(ResourceMgr::GetInstance()->FindRes<Shader>(L"DefaultShader"));

	pBullet->AddComponent(pTransform);
	pBullet->AddComponent(pMeshRender);
	pBullet->AddComponent(new BulletScript);

	BulletScript* pBulletScript = (BulletScript*)pBullet->GetScript<BulletScript>();
	pBulletScript->SetSpeed(500.f);

	SceneMgr::GetInstance()->GetCurScene()->AddObject(L"Bullet", pBullet);
}
