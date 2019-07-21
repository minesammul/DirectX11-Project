#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (m_worldMatrix.worldPosition.y < -500.f || m_bGone == true)
	{
		m_worldMatrix.worldPosition.y = 200.f;

		std::random_device rn;
		std::mt19937_64 rnd(rn());

		std::uniform_int_distribution<int> range(-300, 300);

		m_worldMatrix.worldPosition.x = range(rnd);

		m_bGone = false;
	}
	else
	{
		m_worldMatrix.worldPosition.y -= 200 * DT;
	}
}

TObject Enemy::CreateObject()
{
	TObject createObject;

	TVertex inputVertex;
	inputVertex.vPos = DirectX::XMFLOAT3(-1.f, 1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(1.f, 1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(1.f, -1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(-1.f, -1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	createObject.tIndexOrder = { 
		0, 1, 2,
		0, 2, 3 
	};

	createObject.tWorldMatrix.worldPosition = DirectX::XMFLOAT3(0.f, 170.f, 500.f);
	createObject.tWorldMatrix.worldScale = DirectX::XMFLOAT3(30.f, 30.f, 1.f);
	createObject.tWorldMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	m_worldMatrix = createObject.tWorldMatrix;

	createObject.sName = "enemy";
	m_name = createObject.sName;


	return createObject;
}
