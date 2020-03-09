#pragma once
#include <Script.h>

enum class MUSIC_KIND
{
	IRON_GOLEM_BACKGROUND = 0,
	STAGE_BACKGROUND,
	END
};

enum class MUSIC_STATE
{
	ON=0,
	VOLUME_UP,
	VOLUME_DOWN,
	OFF,
	STOP,
	PLAY,
	END
};

enum class MUSIC_PLAY_KIND
{
	ONE,
	LOOP,
	END
};

struct MusicComponent
{
	MUSIC_STATE musicState;
	CResPtr<CSound> music;
	MUSIC_PLAY_KIND musicPlayKind;
	float startVolume;
	float maxVolume;
};

class CSSN013MusicScript : public CScript
{
private:
	map<MUSIC_KIND, MusicComponent> mMusics;

public:
	CSSN013MusicScript();
	~CSSN013MusicScript();

public:
	virtual void start();
	virtual void update();

	void OperateMusic(MUSIC_KIND musicKind, MUSIC_STATE musicState);
};

