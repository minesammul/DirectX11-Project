#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Update()
{
	if (KEYHOLD(KEY_TYPE::KEY_LEFT))
	{
		m_worldMatrix.worldPosition.x -= m_fSpeed *DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_RIGHT))
	{
		m_worldMatrix.worldPosition.x += m_fSpeed *DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_UP))
	{
		m_worldMatrix.worldPosition.y += m_fSpeed *DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_DOWN))
	{
		m_worldMatrix.worldPosition.y -= m_fSpeed *DT;
	}
}

TObject Player::CreateObject()
{
	TObject createObject;

	TVertex inputVertex;
	inputVertex.vPos = DirectX::XMFLOAT3(0.f, 1.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(1.f, 0.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	inputVertex.vPos = DirectX::XMFLOAT3(-1.f, 0.f, 0.5f);
	inputVertex.vColor = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	createObject.tVertex.push_back(inputVertex);

	createObject.tIndexOrder = { 0, 1, 2 };

	createObject.tWorldMatrix.worldPosition = DirectX::XMFLOAT3(0.f, -200.f, 500.f);
	createObject.tWorldMatrix.worldScale = DirectX::XMFLOAT3(30.f, 30.f, 1.f);
	createObject.tWorldMatrix.worldRotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	m_worldMatrix = createObject.tWorldMatrix;

	createObject.sName = "player";
	m_name = createObject.sName;


	return createObject;
}

