#pragma once
#include <Script.h>

enum class PARTICLE_PLAY_KIND
{
	LOOP,
	ONE,
	END
};

enum class PARTICLE_PLAY_STATE
{
	PLAY,
	STOP,
	DISAPPEAR,
	END
};

class CSSN016ParticleScript : public CScript
{
private:
	float mPlayTime;
	PARTICLE_PLAY_KIND mPlayKind;
	PARTICLE_PLAY_STATE mPlayState;

public:
	CSSN016ParticleScript();
	~CSSN016ParticleScript();

public:
	virtual void start();
	virtual void update();

	void SetPosition(Vec3 position);
	void OperatorParticle(PARTICLE_PLAY_KIND playKind, float minTime, float maxTime, float onePlayTime);
};

