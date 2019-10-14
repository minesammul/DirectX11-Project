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
	
	CGameObject* mousePickingObject;
	DirectX::XMVECTOR mousePickingPosition;

public:
	void RegisterCamera(CCamera* _pCam);
	CScene* GetCurScene() { return m_pCurScene; }

	CGameObject* MousePicking(POINT mousePoint, RECT windowRect);
	CGameObject* GetMousePickingObject();
	DirectX::XMVECTOR GetMousePickingPosition();

public:
	void init();
	void progress();
	void progress_pause();
	void render();

	void FindGameObject(const wstring& _strTagName, vector<CGameObject*>& _vecOut);
	void ChangeScene(CScene* _pNextScene);
};

