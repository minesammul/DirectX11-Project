#pragma once
#include "Object.h"

class StartClient
{
private:
	Graphic m_graphic;
	Object* m_player;
	Object* m_enemy;
	Object* m_bullet;

public:
	StartClient();
	~StartClient();

	void Update();
	void Init(HWND hWnd, bool bWindowed);
	void Render();

	void EnemyBulletCrash();
};

