#include "stdafx.h"
#include "SSN016ParticleScript.h"

#include <ParticleSystem.h>


CSSN016ParticleScript::CSSN016ParticleScript():
	CScript((UINT)SCRIPT_TYPE::SSN016PARTICLESCRIPT)
{
}


CSSN016ParticleScript::~CSSN016ParticleScript()
{
}

void CSSN016ParticleScript::start()
{
	mPlayTime = 0.f;
	mPlayKind = PARTICLE_PLAY_KIND::END;
	mPlayState = PARTICLE_PLAY_STATE::END;
}

void CSSN016ParticleScript::update()
{
	if (mPlayState == PARTICLE_PLAY_STATE::PLAY)
	{
		if (mPlayKind == PARTICLE_PLAY_KIND::ONE)
		{
			mPlayTime -= CTimeMgr::GetInst()->GetDeltaTime();

			if (mPlayTime <= 0.f)
			{
				mPlayState = PARTICLE_PLAY_STATE::DISAPPEAR;
			}
		}
	}
	else if (mPlayState == PARTICLE_PLAY_STATE::DISAPPEAR)
	{
		Object()->Particle()->SetMinLifeTime(0.f);
		Object()->Particle()->SetMaxLifeTime(0.f);
	}

}

void CSSN016ParticleScript::SetPosition(Vec3 position)
{
	Object()->Transform()->SetLocalPos(position);
}

void CSSN016ParticleScript::OperatorParticle(PARTICLE_PLAY_KIND playKind, float minTime, float maxTime, float onePlayTime)
{
	mPlayState = PARTICLE_PLAY_STATE::PLAY;
	mPlayKind = playKind;
	mPlayTime = onePlayTime;

	Object()->Particle()->SetMinLifeTime(minTime);
	Object()->Particle()->SetMaxLifeTime(maxTime);
}

