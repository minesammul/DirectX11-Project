#pragma once
#include <Script.h>
class CTileScript : public CScript
{
private:
	int selectTileX;
	int selectTileY;
	int selectTileIndex;
	int gridCount;
	int textureTileCount;

public:
	CTileScript();
	~CTileScript();

public:
	virtual void awake();
	virtual void update();

	int GetSelectTileX() { return selectTileX; }
	int GetSelectTileY() { return selectTileY; }
	int GetSelectTileIndex() { return selectTileIndex; }
};

