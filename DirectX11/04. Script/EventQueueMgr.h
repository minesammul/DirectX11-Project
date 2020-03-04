#pragma once
#include <queue>

enum class GAME_EVENT_TYPE
{
	HIT,
	ON_MONSTER_UI,
	OFF_MONSTER_UI,
	PLAYER_SP_UPDATE,
	PLAYER_HP_UPDATE,
	MUSIC_MONSTER_BGM_ON,
	MUSIC_MONSTER_BGM_OFF
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
	queue<GameEventComponent> mEvents;

public:
	void AddEvent(GameEventComponent addEvent);
	queue<GameEventComponent>* GetEvents() { return &mEvents; }
};

