#pragma once
#include <Script.h>
class CTileMapScript : public CScript
{
private:
	int referecneTileIndexData[1024];

	const int gridCount = 32;
	CScript* tilesetScript;
	POINT startMousePosition;
public:
	CTileMapScript();
	~CTileMapScript();

public:
	virtual void awake();
	virtual void update();
};

