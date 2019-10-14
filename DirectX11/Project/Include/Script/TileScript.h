#pragma once
#include <Script.h>
class CTileScript : public CScript
{
private:
	int selectTileIndex;
	int gridCount;
	int textureTileCount;

public:
	CTileScript();
	~CTileScript();

public:
	virtual void awake();
	virtual void update();
};

