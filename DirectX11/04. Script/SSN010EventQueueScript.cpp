#include "stdafx.h"
#include "SSN010EventQueueScript.h"

#include "EventQueueMgr.h"
#include "SSN002PlayerScript.h"
#include "SSN007MonsterScript.h"
#include "SSN011PlayerUIScript.h"
#include "SSN013MusicScript.h"
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

		CEventQueueMgr::GetInst()->GetEvents()->pop();
	}
}
