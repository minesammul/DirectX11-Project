#include "stdafx.h"
#include "StartClient.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

StartClient::StartClient()
{
	m_player = new Player;
	m_enemy = new Enemy;
	m_bullet = new Bullet;
}


StartClient::~StartClient()
{
	delete m_player;
	delete m_enemy;
	delete m_bullet;
}

void StartClient::Update()
{
	m_graphic.Update();
	m_player->Update();
	m_graphic.SetWorldMatrix(m_player->GetName(), m_player->GetWorldMatrix());
	m_enemy->Update();
	m_graphic.SetWorldMatrix(m_enemy->GetName(), m_enemy->GetWorldMatrix());
	m_bullet->Update();
	dynamic_cast<Bullet*>(m_bullet)->SetGoalPosition(
		m_player->GetWorldMatrix().worldPosition.x,
		m_player->GetWorldMatrix().worldPosition.y
		);

	m_graphic.SetWorldMatrix(m_bullet->GetName(), m_bullet->GetWorldMatrix());

	EnemyBulletCrash();
}

void StartClient::Init(HWND hWnd, bool bWindowed)
{
	m_graphic.Init(hWnd, bWindowed);
	m_graphic.SaveObjectData(m_player->CreateObject());
	m_graphic.SaveObjectData(m_enemy->CreateObject());
	m_graphic.SaveObjectData(m_bullet->CreateObject());
	m_graphic.ObjectCreate();
}

void StartClient::Render()
{
	m_graphic.Render();
}

void StartClient::EnemyBulletCrash()
{
	if (dynamic_cast<Bullet*>(m_bullet)->IsFire())
	{
		DirectX::XMVECTOR distanceVector = DirectX::XMVectorSet(
			m_enemy->GetWorldMatrix().worldPosition.x - m_bullet->GetWorldMatrix().worldPosition.x,
			m_enemy->GetWorldMatrix().worldPosition.y - m_bullet->GetWorldMatrix().worldPosition.y,
			m_enemy->GetWorldMatrix().worldPosition.z - m_bullet->GetWorldMatrix().worldPosition.z,
			1.f
		);

		distanceVector = DirectX::XMVector3Length(distanceVector);

		float distance = DirectX::XMVectorGetX(distanceVector);

		if (distance < 20.f)
		{
			dynamic_cast<Bullet*>(m_bullet)->SetFire(false);
			dynamic_cast<Enemy*>(m_enemy)->SetGone(true);
		}
	}
}
