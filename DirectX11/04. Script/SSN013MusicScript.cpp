#include "stdafx.h"
#include "SSN013MusicScript.h"


CSSN013MusicScript::CSSN013MusicScript() :
	CScript((UINT)SCRIPT_TYPE::SSN013MUSICSCRIPT)
{
}


CSSN013MusicScript::~CSSN013MusicScript()
{
}

void CSSN013MusicScript::start()
{
	for (int index = 0; index < (int)MUSIC_KIND::END; index++)
	{
		MusicComponent inputData;
		if (index == (int)MUSIC_KIND::IRON_GOLEM_BACKGROUND)
		{
			inputData.musicState = MUSIC_STATE::OFF;
			inputData.music = CResMgr::GetInst()->Load<CSound>(L"IronGolemBGM.mp3", L"Sound\\IronGolemBGM.mp3");
			mMusics[(MUSIC_KIND)index] = inputData;
		}
	}

}

void CSSN013MusicScript::update()
{
	map<MUSIC_KIND, MusicComponent>::iterator musicIter = mMusics.begin();
	while (musicIter != mMusics.end())
	{
		if (musicIter->second.musicState == MUSIC_STATE::ON)
		{
			musicIter->second.music->Play(1);
			musicIter->second.music->SetVolume(0.f);

			musicIter->second.musicState = MUSIC_STATE::VOLUME_UP;
		}
		else if (musicIter->second.musicState == MUSIC_STATE::VOLUME_UP)
		{
			float volume = musicIter->second.music->GetVolume();
			if (volume < 0.5f)
			{
				volume += CTimeMgr::GetInst()->GetDeltaTime() * 0.1f;
				musicIter->second.music->SetVolume(volume);
			}
			else
			{
				volume = 0.5f;
				musicIter->second.music->SetVolume(volume);
				musicIter->second.musicState = MUSIC_STATE::PLAY;
			}
		}
		else if (musicIter->second.musicState == MUSIC_STATE::VOLUME_DOWN)
		{
			float volume = musicIter->second.music->GetVolume();
			if (volume > 0.f)
			{
				volume -= CTimeMgr::GetInst()->GetDeltaTime() * 0.1f;
				musicIter->second.music->SetVolume(volume);
			}
			else
			{
				volume = 0.f;
				musicIter->second.music->SetVolume(volume);
				musicIter->second.music->Stop();
				musicIter->second.musicState = MUSIC_STATE::STOP;
			}
		}
		else if (musicIter->second.musicState == MUSIC_STATE::OFF)
		{
			musicIter->second.musicState = MUSIC_STATE::VOLUME_DOWN;
		}

		musicIter++;
	}
}

void CSSN013MusicScript::OperateMusic(MUSIC_KIND musicKind, MUSIC_STATE musicState)
{
	mMusics[musicKind].musicState = musicState;
}