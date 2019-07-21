#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	m_bFire = false;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (KEYHOLD(KEY_TYPE::KEY_SPACE))
	{
		m_bFire = true;
	}
	BulletFire();
}

TObject Bullet::CreateObject()
{
	TObject createObject;

	TVertex inputVertex;

	inputVertex.vPos = DirectX::XMFLOAT3(0.f, 0.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(0.f, 1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(0.6f, 0.6f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(1.f, 0.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(0.6f, -0.6f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(0.f, -1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(-0.6f, -0.6f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(-1.0f, 0.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(-0.6f, 0.6f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	createObject.tIndexOrder = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1
	};

	createObject.tWorldMatrix.worldPosition = DirectX::XMFLOAT3(0.f, 0.f, 500.f);
	createObject.tWorldMatrix.worldScale = DirectX::XMFLOAT3(5.f, 5.f, 1.f);
	createObject.tWorldMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

	m_worldMatrix = createObject.tWorldMatrix;

	createObject.sName = "bullet";
	m_name = createObject.sName;


	return createObject;
}

void Bullet::BulletFire()
{

	if (m_bFire == false)
	{
		m_worldMatrix.worldPosition.x = m_tGoal.x;
		m_worldMatrix.worldPosition.y = m_tGoal.y + 10;
	}
	else
	{
		m_worldMatrix.worldPosition.y += 300 * DT;

		if (m_worldMatrix.worldPosition.y > 500)
		{
			m_bFire = false;
		}
	}
}
