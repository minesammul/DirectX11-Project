#pragma once
#include <queue>

enum class GAME_EVENT_TYPE
{
	HIT,
	ON_MONSTER_UI,
	OFF_MONSTER_UI,
	PLAYER_SP_UPDATE,
	PLAYER_HP_UPDATE,
	PLAYER_ITEM_HEAL_UPDATE,
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
	ON_EFFECT_SOUND_BOSSOUT,
	PARTICLE_RAIN_START,
	PARTICLE_RAIN_STOP,
	PARTICLE_DOOR_START,
	PARTICLE_DOOR_STOP,
	PARTICLE_HEAL_START,
	PARTICLE_MONSTER_DEAD_START,
	LIGHT_MOVE,
	EFFECT_THUNDER_ON,
	EFFECT_THUNDER_OFF,
	DECAL_THUNDER_ON,
	OFF_INOUTSIDE_MESH,
	START_MONSER_DEAD_LIGHT_UI
};

union SendData
{
	int intValue;
	UINT uintValue;
	float floatValue;
};

struct GameEventComponent
{
	GAME_EVENT_TYPE eventType;
	wstring sendObjectName;
	wstring receiveObjectName;
	vector<SendData> sendObjectData;
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

