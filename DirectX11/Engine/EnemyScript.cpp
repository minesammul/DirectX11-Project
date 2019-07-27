#include "stdafx.h"
#include "EnemyScript.h"
#include "BulletScript.h"
#include <random>

EnemyScript::EnemyScript()
{
}


EnemyScript::~EnemyScript()
{
}

void EnemyScript::Update()
{
	GameObject* pObj = Object();

	DirectX::XMFLOAT3 vPos = pObj->GetTransform()->GetLocalPos();

	vPos.y -= 100.f*DT;

	if (vPos.y < -300 || IsCollision()==true)
	{
		vPos.y = 300.f;
		std::random_device rn;
		std::mt19937_64 rnd(rn());

		std::uniform_int_distribution<int> range(-200, 200);
		vPos.x = range(rnd);
	}

	pObj->GetTransform()->SetLocalPos(vPos);
}

bool EnemyScript::IsCollision()
{
	unsigned int uiBulletCount = SceneMgr::GetInstance()->GetCurScene()->FindLayer(L"Bullet")->GetGameObject().size();
	for (int index = 0; index < uiBulletCount; index++)
	{
		GameObject* pBullet = SceneMgr::GetInstance()->GetCurScene()->FindLayer(L"Bullet")->GetGameObject()[index];
		DirectX::XMVECTOR distance = DirectX::XMVectorSet(
			pBullet->GetTransform()->GetLocalPos().x - Object()->GetTransform()->GetLocalPos().x,
			pBullet->GetTransform()->GetLocalPos().y - Object()->GetTransform()->GetLocalPos().y,
			pBullet->GetTransform()->GetLocalPos().z - Object()->GetTransform()->GetLocalPos().z,
			1
		);

		distance = DirectX::XMVector3Length(distance);
		float range = 10.f;
		if (DirectX::XMVectorGetX(distance) < range)
		{
			return true;
		}
	}
	return false;
}
