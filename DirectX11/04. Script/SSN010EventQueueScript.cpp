#include "stdafx.h"
#include "SSN010EventQueueScript.h"

#include "EventQueueMgr.h"
#include "SSN002PlayerScript.h"
#include "SSN007MonsterScript.h"

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
				CGameObject* receiveObject = findObject[0];

				for (int index = 0; index < receiveObject->GetScripts().size(); index++)
				{
					if (receiveObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT)
					{
						CSSN002PlayerScript* playerScript = dynamic_cast<CSSN002PlayerScript*>(receiveObject->GetScripts()[index]);
						playerScript->SetHit(true);
					}
					else if (receiveObject->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN007MONSTERSCRIPT)
					{

					}
				}

			}
		}


		CEventQueueMgr::GetInst()->GetEvents()->pop();
	}
}
