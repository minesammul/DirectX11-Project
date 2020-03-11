#include "stdafx.h"
#include "SSN010EventQueueScript.h"

#include <GameObject.h>
#include <ParticleSystem.h>

#include "EventQueueMgr.h"
#include "SSN002PlayerScript.h"
#include "SSN007MonsterScript.h"
#include "SSN011PlayerUIScript.h"
#include "SSN013MusicScript.h"
#include "SSN012SkyBoxScript.h"
#include "SSN014DirectionLightScript.h"
#include "SSN018EffectScript.h"
#include "SSN016ParticleScript.h"
#include "FunctionMgr.h"

CSSN010EventQueueScript::CSSN010EventQueueScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN010EVENTQUEUESCRIPT)
{
}


CSSN010EventQueueScript::~CSSN010EventQueueScript()
{
}

void CSSN010EventQueueScript::update()
{
	if (CEventQueueMgr::GetInst()->GetEvents()->empty() == false)
	{
		GameEventComponent popEvent = CEventQueueMgr::GetInst()->GetEvents()->front();

		if (popEvent.eventType == GAME_EVENT_TYPE::HIT)
		{
			CSSN011PlayerUIScript* playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(CFunctionMgr::GetInst()->FindScript(L"PlayerUI", SCRIPT_TYPE::SSN011PLAYERUISCRIPT));

			CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.receiveObjectName, SCRIPT_TYPE::SSN002PLAYERSCRIPT));
			CSSN007MonsterScript* monsterScript = dynamic_cast<CSSN007MonsterScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.receiveObjectName, SCRIPT_TYPE::SSN007MONSTERSCRIPT));

			if (playerScript != nullptr)
			{
				playerScript->SetHit(true);

				int playerHP = playerScript->GetPlayerHP();
				playerUIScript->CalculationPlayerHPUI(playerHP);
			}
			else if (monsterScript != nullptr)
			{
				monsterScript->SetHit(true);

				int monsterHP = monsterScript->GetMonsterHP();
				playerUIScript->CalculationMonsterHPUI(monsterHP);
			}

		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::ON_MONSTER_UI)
		{
			CSSN011PlayerUIScript* playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(CFunctionMgr::GetInst()->FindScript(L"PlayerUI", SCRIPT_TYPE::SSN011PLAYERUISCRIPT));
			CSSN007MonsterScript* monsterScript = dynamic_cast<CSSN007MonsterScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.sendObjectName, SCRIPT_TYPE::SSN007MONSTERSCRIPT));

			int monsterMaxHP = monsterMaxHP = monsterScript->GetMonsterHP();

			playerUIScript->OnMonsterUI();
			playerUIScript->SetMonsterHPRation(monsterMaxHP);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PLAYER_SP_UPDATE)
		{
			CSSN011PlayerUIScript* playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(CFunctionMgr::GetInst()->FindScript(L"PlayerUI", SCRIPT_TYPE::SSN011PLAYERUISCRIPT));
			CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.sendObjectName, SCRIPT_TYPE::SSN002PLAYERSCRIPT));
			
			int playerMaxSP = playerScript->GetPlayerMaxSP();
			int playerSP = playerScript->GetPlayerSP();

			playerUIScript->SetPlayerSPRation(playerMaxSP);
			playerUIScript->CalculationPlayerSPUI(playerSP);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PLAYER_HP_UPDATE)
		{
			CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.sendObjectName, SCRIPT_TYPE::SSN002PLAYERSCRIPT));
			CSSN011PlayerUIScript* playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(CFunctionMgr::GetInst()->FindScript(L"PlayerUI", SCRIPT_TYPE::SSN011PLAYERUISCRIPT));

			int playerMaxHP = playerScript->GetPlayerMaxHP();
			int playerHP = playerScript->GetPlayerHP();
			playerUIScript->SetPlayerHPRation(playerMaxHP);
			playerUIScript->CalculationPlayerHPUI(playerHP);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PLAYER_ITEM_HEAL_UPDATE)
		{
			CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.sendObjectName, SCRIPT_TYPE::SSN002PLAYERSCRIPT));
			CSSN011PlayerUIScript* playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(CFunctionMgr::GetInst()->FindScript(L"PlayerUI", SCRIPT_TYPE::SSN011PLAYERUISCRIPT));

			int playerMaxHealCount = playerScript->GetPlayerMaxHealCount();
			int playerHealCount = playerScript->GetPlayerHealCount();
			playerUIScript->CalculationPlayerHealUI(playerMaxHealCount, playerHealCount);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::MUSIC_MONSTER_BGM_ON)
		{
			CSSN013MusicScript* musicScript = dynamic_cast<CSSN013MusicScript*>(CFunctionMgr::GetInst()->FindScript(L"Music", SCRIPT_TYPE::SSN013MUSICSCRIPT));
			
			musicScript->OperateMusic(MUSIC_KIND::STAGE_BACKGROUND, MUSIC_STATE::OFF);
			musicScript->OperateMusic(MUSIC_KIND::IRON_GOLEM_BACKGROUND, MUSIC_STATE::ON);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::MUSIC_MONSTER_BGM_OFF)
		{
			CSSN013MusicScript* musicScript = dynamic_cast<CSSN013MusicScript*>(CFunctionMgr::GetInst()->FindScript(L"Music", SCRIPT_TYPE::SSN013MUSICSCRIPT));

			musicScript->OperateMusic(MUSIC_KIND::IRON_GOLEM_BACKGROUND, MUSIC_STATE::OFF);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::SKY_CHANGE_BATTLE)
		{
			CSSN012SkyBoxScript* skyBoxScript = dynamic_cast<CSSN012SkyBoxScript*>(CFunctionMgr::GetInst()->FindScript(L"Skybox", SCRIPT_TYPE::SSN012SKYBOXSCRIPT));
			
			CResPtr<CTexture> skyTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\DarkStorm4K.png");
			skyBoxScript->StartBlendSky(skyTexture, 0.1f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::SKY_CHANGE_CLEAR)
		{
			CSSN012SkyBoxScript* skyBoxScript = dynamic_cast<CSSN012SkyBoxScript*>(CFunctionMgr::GetInst()->FindScript(L"Skybox", SCRIPT_TYPE::SSN012SKYBOXSCRIPT));

			CResPtr<CTexture> skyTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\Epic_GloriousPink_EquiRect.png");
			skyBoxScript->StartBlendSky(skyTexture, 0.15f);
			skyBoxScript->SetUVSpeed(0.0005f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::INSIDE_LIGHT)
		{
			CSSN014DirectionLightScript* lightScript = dynamic_cast<CSSN014DirectionLightScript*>(CFunctionMgr::GetInst()->FindScript(L"DirectionLight1", SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT));
			lightScript->StartLightVoluemUp(	Vec3(0.f, 0.f, 0.f),
												Vec3(0.f, 0.f, 0.f),
												Vec3(0.3f, 0.3f, 0.3f),
												Vec3(0.f, 0.f, 0.f),
												Vec3(0.2f, 0.2f, 0.2f), 
												Vec3(0.3f, 0.3f, 0.3f),
												0.04f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::OUTSIDE_LIGHT)
		{
			CSSN014DirectionLightScript* lightScript = dynamic_cast<CSSN014DirectionLightScript*>(CFunctionMgr::GetInst()->FindScript(L"DirectionLight1", SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT));
			lightScript->StartLightVoluemDown(	Vec3(1.f, 1.f, 1.f),
												Vec3(1.f, 1.f, 1.f),
												Vec3(0.3f, 0.3f, 0.3f),
												Vec3(0.1f, 0.1f, 0.1f),
												Vec3(0.3f, 0.3f, 0.3f),
												Vec3(1.f, 1.f, 1.f),
												0.5f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::CLEAR_LIGHT)
		{
			CSSN014DirectionLightScript* lightScript = dynamic_cast<CSSN014DirectionLightScript*>(CFunctionMgr::GetInst()->FindScript(L"DirectionLight1", SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT));
			lightScript->StartLightVoluemUp(	Vec3(0.1f, 0.1f, 0.1f),
												Vec3(0.3f, 0.3f, 0.3f),
												Vec3(1.f, 1.f, 1.f),
												Vec3(0.1f, 0.1f, 0.1f),
												Vec3(0.8f, 0.8f, 0.8f),
												Vec3(0.9f, 0.9f, 0.9f),
												0.09f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::ON_EFFECT_SOUND_THUNDER)
		{
			CSSN013MusicScript* musicScript = dynamic_cast<CSSN013MusicScript*>(CFunctionMgr::GetInst()->FindScript(L"Music", SCRIPT_TYPE::SSN013MUSICSCRIPT));
			musicScript->OperateMusic(MUSIC_KIND::EFFECT_THUNDER, MUSIC_STATE::ON);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::ON_EFFECT_SOUND_WIND)
		{
			CSSN013MusicScript* musicScript = dynamic_cast<CSSN013MusicScript*>(CFunctionMgr::GetInst()->FindScript(L"Music", SCRIPT_TYPE::SSN013MUSICSCRIPT));
			musicScript->OperateMusic(MUSIC_KIND::EFFECT_WIND, MUSIC_STATE::ON);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::OFF_EFFECT_SOUND_WIND)
		{
			CSSN013MusicScript* musicScript = dynamic_cast<CSSN013MusicScript*>(CFunctionMgr::GetInst()->FindScript(L"Music", SCRIPT_TYPE::SSN013MUSICSCRIPT));
			musicScript->OperateMusic(MUSIC_KIND::EFFECT_WIND, MUSIC_STATE::OFF);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PARTICLE_RAIN_START)
		{
			vector<CGameObject*> allParticle = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Particle")->GetParentObject();
			for (int index = 0; index < allParticle.size(); index++)
			{
				if (allParticle[index]->GetName().find(L"Rain") != wstring::npos)
				{
					allParticle[index]->Active(true);
				}
			}
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PARTICLE_RAIN_STOP)
		{
			vector<CGameObject*> allParticle = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Particle")->GetParentObject();
			for (int index = 0; index < allParticle.size(); index++)
			{
				if (allParticle[index]->GetName().find(L"Rain") != wstring::npos)
				{
					allParticle[index]->Particle()->SetMinLifeTime(0.f);
					allParticle[index]->Particle()->SetMaxLifeTime(0.f);
				}
			}
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PARTICLE_DOOR_START)
		{
			vector<CGameObject*> allParticle = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Particle")->GetParentObject();
			for (int index = 0; index < allParticle.size(); index++)
			{
				if (allParticle[index]->GetName().find(L"Door") != wstring::npos)
				{
					allParticle[index]->Active(true);
				}
			}
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PARTICLE_DOOR_STOP)
		{
			vector<CGameObject*> allParticle = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Particle")->GetParentObject();
			for (int index = 0; index < allParticle.size(); index++)
			{
				if (allParticle[index]->GetName().find(L"Door") != wstring::npos)
				{
					allParticle[index]->Particle()->SetMinLifeTime(0.f);
					allParticle[index]->Particle()->SetMaxLifeTime(0.f);
				}
			}
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PARTICLE_HEAL_START)
		{
			CSSN016ParticleScript* particleScript = dynamic_cast<CSSN016ParticleScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.receiveObjectName, SCRIPT_TYPE::SSN016PARTICLESCRIPT));
			particleScript->OperatorParticle(PARTICLE_PLAY_KIND::ONE, 6.f, 6.f, 1.f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::LIGHT_MOVE)
		{
			CSSN014DirectionLightScript* lightScript = dynamic_cast<CSSN014DirectionLightScript*>(CFunctionMgr::GetInst()->FindScript(L"DirectionLight1", SCRIPT_TYPE::SSN014DIRECTIONLIGHTSCRIPT));
			
			float xValue = popEvent.sendObjectData[0].floatValue;
			float yValue = popEvent.sendObjectData[1].floatValue;
			float zValue = popEvent.sendObjectData[2].floatValue;
			
			Vec3 nowLightPosition = lightScript->GetPosition();
			Vec3 changeLightPosition = nowLightPosition + Vec3(xValue, yValue, zValue);
			
			lightScript->SetPosition(changeLightPosition);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::EFFECT_THUNDER_ON)
		{
			CSSN018EffectScript* effectScript = dynamic_cast<CSSN018EffectScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.receiveObjectName, SCRIPT_TYPE::SSN018EFFECTSCRIPT));

			effectScript->OperaterEffect(EFFECT_KIND::THUNDER_EFFECT, EFFECT_OPERATER_KIND::UP, 0.5f);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::EFFECT_THUNDER_OFF)
		{
			CSSN018EffectScript* effectScript = dynamic_cast<CSSN018EffectScript*>(CFunctionMgr::GetInst()->FindScript(popEvent.receiveObjectName, SCRIPT_TYPE::SSN018EFFECTSCRIPT));

			effectScript->OperaterEffect(EFFECT_KIND::THUNDER_EFFECT, EFFECT_OPERATER_KIND::DOWN, 1.f);
		}

		CEventQueueMgr::GetInst()->GetEvents()->pop();
	}
}
