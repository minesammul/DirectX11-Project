#pragma once

class Scene;

class SceneMgr
{
private:
	Scene * m_pCurScene;
	Scene* m_pNextScene;

public:
	SceneMgr();
	~SceneMgr();

public:
	static SceneMgr* GetInstance()
	{
		static SceneMgr instance;
		return &instance;
	}

public:
	void Init();
	void Progress();
	void Render();

};

