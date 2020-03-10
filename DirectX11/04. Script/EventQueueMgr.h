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
	MUSIC_MONSTER_BGM_OFF,
	SKY_CHANGE_BATTLE,
	SKY_CHANGE_CLEAR,
	INSIDE_LIGHT,
	OUTSIDE_LIGHT,
	CLEAR_LIGHT,
	ON_EFFECT_SOUND_THUNDER,
	ON_EFFECT_SOUND_WIND,
	OFF_EFFECT_SOUND_WIND,
	PARTICLE_RAIN_START,
	PARTICLE_RAIN_STOP
};

union SendData
{
	int intValue;
	UINT uintValue;
};

struct GameEventComponent
{
	GAME_EVENT_TYPE eventType;
	wstring sendObjectName;
	wstring receiveObjectName;
	SendData sendObjectData;
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

