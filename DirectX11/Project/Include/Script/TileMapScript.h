#pragma once
#include <Script.h>

class CCamera;
class CTileMapScript : public CScript
{
private:
	CResPtr<CMaterial>  m_pCloneMtrl;

	int referecneTileIndexData[1024];

	const int GRID_COUNT = 32;
	CScript* tilesetScript;
	POINT startMousePosition;
	const float TILE_MOVE_SPEED = 200.f;
	const float TILE_SCALE_MULTI_VALUE = 1.2f;
	CCamera* tileMapCamera;

public:
	CTileMapScript();
	~CTileMapScript();

public:
	virtual void awake();
	virtual void update();
	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	void EditTileMap();
	void EditMoveTileMap();
};

