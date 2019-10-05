#pragma once

class CScene;
class CCamera;
class CGameObject;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*	m_pCurScene;
	CScene* m_pNextScene;
	   	 
public:
	void RegisterCamera(CCamera* _pCam);
	CScene* GetCurScene() { return m_pCurScene; }

	CGameObject* MousePicking(POINT mousePoint, RECT windowRect);

public:
	void init();
	void progress();
	void progress_pause();
	void render();

	void FindGameObject(const wstring& _strTagName, vector<CGameObject*>& _vecOut);


	// юс╫ц
private:
	void CreatePrefab();
};

