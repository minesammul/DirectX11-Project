#pragma once
#include <Script.h>

class CSSN010EventQueueScript : public CScript
{
public:
	CSSN010EventQueueScript();
	~CSSN010EventQueueScript();

private:
	//CScript* FindScript(wstring objectName, SCRIPT_TYPE scriptType);

public:
	virtual void update();
};

