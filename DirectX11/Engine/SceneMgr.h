#pragma once

class Scene;
class Camera;

class SceneMgr
{
private:
	Scene * m_pCurScene;
	Scene* m_pNextScene;

public:
	SceneMgr();
	~SceneMgr();

private:
	void CreatePrefab();

public:
	void RegisterCamera(Camera* _pCam);
	Scene* GetCurScene() { return m_pCurScene; }

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

