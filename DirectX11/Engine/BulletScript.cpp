#include "stdafx.h"
#include "BulletScript.h"


BulletScript::BulletScript():
	m_fSpeed(200.f)
{
}


BulletScript::~BulletScript()
{
}

void BulletScript::Update()
{
	DirectX::XMFLOAT3 vPos = GetTransform()->GetLocalPos();

	vPos.y += m_fSpeed * DT;

	GetTransform()->SetLocalPos(vPos);
}
