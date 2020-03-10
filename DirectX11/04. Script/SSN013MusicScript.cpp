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
			inputData.maxVolume = 0.5f;
			inputData.startVolume = 0.f;
			inputData.musicPlayKind = MUSIC_PLAY_KIND::LOOP;
			mMusics[(MUSIC_KIND)index] = inputData;
		}
		else if (index == (int)MUSIC_KIND::STAGE_BACKGROUND)
		{
			inputData.musicState = MUSIC_STATE::ON;
			inputData.music = CResMgr::GetInst()->Load<CSound>(L"StageBGM.mp3", L"Sound\\stageBGM.mp3");
			inputData.maxVolume = 0.5f;
			inputData.startVolume = 0.f;
			inputData.musicPlayKind = MUSIC_PLAY_KIND::LOOP;
			mMusics[(MUSIC_KIND)index] = inputData;
		}
		else if (index == (int)MUSIC_KIND::EFFECT_THUNDER)
		{
			inputData.musicState = MUSIC_STATE::OFF;
			inputData.music = CResMgr::GetInst()->Load<CSound>(L"ThunderSound.mp3", L"Sound\\ThunderSound.mp3");
			inputData.maxVolume = 1.0f;
			inputData.startVolume = 1.0f;
			inputData.musicPlayKind = MUSIC_PLAY_KIND::ONE;
			mMusics[(MUSIC_KIND)index] = inputData;
		}
		else if (index == (int)MUSIC_KIND::EFFECT_WIND)
		{
			inputData.musicState = MUSIC_STATE::OFF;
			inputData.music = CResMgr::GetInst()->Load<CSound>(L"deathwind.mp3", L"Sound\\deathwind.mp3");
			inputData.maxVolume = 0.5f;
			inputData.startVolume = 0.f;
			inputData.musicPlayKind = MUSIC_PLAY_KIND::LOOP;
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
			if (musicIter->second.musicPlayKind == MUSIC_PLAY_KIND::LOOP)
			{
				musicIter->second.music->Play(-1);
			}
			else if (musicIter->second.musicPlayKind == MUSIC_PLAY_KIND::ONE)
			{
				musicIter->second.music->Play(1);
			}
			
			float nowMusicStartVolume = musicIter->second.startVolume;
			musicIter->second.music->SetVolume(nowMusicStartVolume);

			musicIter->second.musicState = MUSIC_STATE::VOLUME_UP;
		}
		else if (musicIter->second.musicState == MUSIC_STATE::VOLUME_UP)
		{
			float maxVolume = musicIter->second.maxVolume;
			float volume = musicIter->second.music->GetVolume();
			if (volume < maxVolume)
			{
				volume += CTimeMgr::GetInst()->GetDeltaTime() * 0.1f;
				musicIter->second.music->SetVolume(volume);
			}
			else
			{
				volume = maxVolume;
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
		else if (musicIter->second.musicState == MUSIC_STATE::PLAY)
		{
			if ((musicIter->second.musicPlayKind == MUSIC_PLAY_KIND::ONE))
			{
				bool nowMusicIsPlaying = musicIter->second.music->IsPlaying();
				if (nowMusicIsPlaying == false)
				{
					musicIter->second.musicState = MUSIC_STATE::STOP;
				}
			}
		}

		musicIter++;
	}
}

void CSSN013MusicScript::OperateMusic(MUSIC_KIND musicKind, MUSIC_STATE musicState)
{
	mMusics[musicKind].musicState = musicState;
}