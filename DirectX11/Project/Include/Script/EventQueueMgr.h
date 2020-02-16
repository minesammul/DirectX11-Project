#pragma once
#include <queue>

enum class GAME_EVENT_TYPE
{
	HIT
};

struct GameEventComponent
{
	GAME_EVENT_TYPE eventType;
	wstring sendObjectName;
	wstring receiveObjectName;
};

class CEventQueueMgr
{
	SINGLE(CEventQueueMgr);

private:
	queue<GameEventComponent> events;

public:
	void AddEvent(GameEventComponent addEvent);
	queue<GameEventComponent>* GetEvents() { return &events; }
};

