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
	Prefab* pBulletPrefab = ResourceMgr::GetInstance()->FindRes<Prefab>(L"BulletPrefab");
	GameObject* pClone = pBulletPrefab->Instantiate();
	pClone->GetTransform()->SetLocalPos(GetTransform()->GetLocalPos());
	SceneMgr::GetInstance()->GetCurScene()->AddObject(L"Bullet", pClone);

}
