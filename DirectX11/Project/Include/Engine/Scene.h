#pragma once
#include "Entity.h"

class CLayer;
class CGameObject;
class CCamera;

class CScene :
	public CEntity
{
private:
	CLayer*				m_arrLayer[MAX_LAYER];
	CCamera*			m_arrCam[MAX_CAM];
	int					m_iCamCount;

public:
	void awake();
	void start();

	void update();
	void lateupdate();
	void finalupdate();

public:
	void AddLayer(const wstring& _strLayerName, UINT _iLayerIdx);
	void AddLayer(CLayer* _pLayer, UINT _iLayerIdx);

	void AddObject(const wstring& _strLayerName, CGameObject* _pObj, bool _bMoveAll = true);
	void AddObject(UINT _iLayerIdx, CGameObject* _pObj, bool _bAllMove);
	
	void AddCamera(CCamera* _pCam);
	CCamera* GetCamera(int index)
	{
		return m_arrCam[index];
	}

	CLayer* FindLayer(const wstring& _strLayer);
	CLayer* GetLayer(int _iLayerIdx) 
	{ 
		if (_iLayerIdx == -1)
		{
			return nullptr;
		}

		return m_arrLayer[_iLayerIdx];
	}
	CGameObject* FindGameObject(const wstring& _strName, vector<CGameObject*>& _vecOut);
	bool IsExistGameObjectName(const wstring& _strName);

	void ResetRegisterCam()
	{
		memset(m_arrCam, 0, sizeof(void*)*MAX_CAM);
		m_iCamCount = 0;
	}

public:
	CLONE_DISABLE(CScene);

public:
	CScene();
	~CScene();
};

