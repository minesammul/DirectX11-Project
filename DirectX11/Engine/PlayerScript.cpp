#include "stdafx.h"
#include "PlayerScript.h"

#include "KeyMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "TimeMgr.h"

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

	// Ű�Է����� �ﰢ�� �����̱�
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
}
