#pragma once
#include <Script.h>

enum class MUSIC_KIND
{
	IRON_GOLEM_BACKGROUND = 0,
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

struct MusicComponent
{
	MUSIC_STATE musicState;
	CResPtr<CSound> music;
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

	void OnMusic(MUSIC_KIND musicKind, MUSIC_STATE musicState);
	void OffMusic(MUSIC_KIND musicKind, MUSIC_STATE musicState);
};

