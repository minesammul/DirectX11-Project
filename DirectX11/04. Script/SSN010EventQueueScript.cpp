#include "stdafx.h"
#include "SSN010EventQueueScript.h"

#include "EventQueueMgr.h"
#include "SSN002PlayerScript.h"
#include "SSN007MonsterScript.h"
#include "SSN011PlayerUIScript.h"

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
			vector<CGameObject*> findObject;
			CSceneMgr::GetInst()->GetCurScene()->FindGameObject(popEvent.receiveObjectName,findObject);

			if (findObject.empty()==false)
			{
				vector<CGameObject*> UIObject;
				CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerUI", UIObject);
				CGameObject* playerUIObject = UIObject[0];
				CSSN011PlayerUIScript* playerUIScript = nullptr;
				for (int index = 0; index < playerUIObject->GetScripts().size(); index++)
				{
					if (playerUIObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN011PLAYERUISCRIPT)
					{
						playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(playerUIObject->GetScripts()[index]);
						break;
					}
				}


				CGameObject* receiveObject = findObject[0];
				for (int index = 0; index < receiveObject->GetScripts().size(); index++)
				{
					if (receiveObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT)
					{
						CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(receiveObject->GetScripts()[index]);
						playerScript->SetHit(true);

						int playerHP = playerScript->GetPlayerHP();
						playerUIScript->CalculationPlayerHPUI(playerHP);
					}
					else if (receiveObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN007MONSTERSCRIPT)
					{
						CSSN007MonsterScript* monsterScript = dynamic_cast<CSSN007MonsterScript*>(receiveObject->GetScripts()[index]);
						monsterScript->SetHit(true);

						int monsterHP = monsterScript->GetMonsterHP();
						playerUIScript->CalculationMonsterHPUI(monsterHP);
					}
				}

			}
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::ON_MONSTER_UI)
		{
			vector<CGameObject*> findObject;
			CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerUI", findObject);

			if (findObject.empty() == false)
			{
				vector<CGameObject*> mosnterObject;
				CSceneMgr::GetInst()->GetCurScene()->FindGameObject(popEvent.sendObjectName, mosnterObject);
				CGameObject* sendObject = mosnterObject[0];

				int monsterMaxHP = 0;
				for (int index = 0; index < sendObject->GetScripts().size(); index++)
				{
					if (sendObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN007MONSTERSCRIPT)
					{
						CSSN007MonsterScript* monsterScript = dynamic_cast<CSSN007MonsterScript*>(sendObject->GetScripts()[index]);
						monsterMaxHP = monsterScript->GetMonsterHP();
					}
				}


				CGameObject* receiveObject = findObject[0];
				for (int index = 0; index < receiveObject->GetScripts().size(); index++)
				{
					if (receiveObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN011PLAYERUISCRIPT)
					{
						CSSN011PlayerUIScript* playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(receiveObject->GetScripts()[index]);
						playerUIScript->OnMonsterUI();
						playerUIScript->SetMonsterHPRation(monsterMaxHP);
					}
				}

			}
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PLAYER_SP_UPDATE)
		{
			CSSN002PlayerScript* playerScript = nullptr;
			CSSN011PlayerUIScript* playerUIScript = nullptr;
			
			{
				vector<CGameObject*> findObject;
				CSceneMgr::GetInst()->GetCurScene()->FindGameObject(popEvent.sendObjectName, findObject);
				
				for (int index = 0; index < findObject[0]->GetScripts().size(); index++)
				{
					if (findObject[0]->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT)
					{
						playerScript = dynamic_cast<CSSN002PlayerScript*>(findObject[0]->GetScripts()[index]);
						break;
					}
				}
			}

			{
				vector<CGameObject*> findObject;
				CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerUI", findObject);
				
				for (int index = 0; index < findObject[0]->GetScripts().size(); index++)
				{
					if (findObject[0]->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN011PLAYERUISCRIPT)
					{
						playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(findObject[0]->GetScripts()[index]);
						break;
					}
				}
			}

			int playerMaxSP = playerScript->GetPlayerMaxSP();
			int playerSP = playerScript->GetPlayerSP();
			playerUIScript->SetPlayerSPRation(playerMaxSP);
			playerUIScript->CalculationPlayerSPUI(playerSP);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::PLAYER_HP_UPDATE)
		{
			CSSN002PlayerScript* playerScript = nullptr;
			CSSN011PlayerUIScript* playerUIScript = nullptr;

			{
				vector<CGameObject*> findObject;
				CSceneMgr::GetInst()->GetCurScene()->FindGameObject(popEvent.sendObjectName, findObject);

				for (int index = 0; index < findObject[0]->GetScripts().size(); index++)
				{
					if (findObject[0]->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT)
					{
						playerScript = dynamic_cast<CSSN002PlayerScript*>(findObject[0]->GetScripts()[index]);
						break;
					}
				}
			}

			{
				vector<CGameObject*> findObject;
				CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerUI", findObject);

				for (int index = 0; index < findObject[0]->GetScripts().size(); index++)
				{
					if (findObject[0]->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN011PLAYERUISCRIPT)
					{
						playerUIScript = dynamic_cast<CSSN011PlayerUIScript*>(findObject[0]->GetScripts()[index]);
						break;
					}
				}
			}

			int playerMaxHP = playerScript->GetPlayerMaxHP();
			int playerHP = playerScript->GetPlayerHP();
			playerUIScript->SetPlayerHPRation(playerMaxHP);
			playerUIScript->CalculationPlayerHPUI(playerHP);
		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::MUSIC_SLOW_ON)
		{

		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::MUSIC_FAST_ON)
		{

		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::MUSIC_SLOW_OFF)
		{

		}
		else if (popEvent.eventType == GAME_EVENT_TYPE::MUSIC_FAST_OFF)
		{

		}

		CEventQueueMgr::GetInst()->GetEvents()->pop();
	}
}
