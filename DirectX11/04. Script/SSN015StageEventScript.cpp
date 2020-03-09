#include "stdafx.h"
#include "SSN015StageEventScript.h"

#include "SSN013MusicScript.h"
#include "EventQueueMgr.h"

CSSN015StageEventScript::CSSN015StageEventScript():
	CScript((UINT)SCRIPT_TYPE::SSN015STAGEEVENTSCRIPT)
{
}


CSSN015StageEventScript::~CSSN015StageEventScript()
{
}

void CSSN015StageEventScript::OnCollisionEnter(CCollider3D * _pOther)
{
	if (_pOther->Object()->GetName() == L"PlayerEventMesh")
	{
		if (Object()->GetName() == L"EventStartBattle")
		{
			{			
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::SKY_CHANGE_BATTLE;
				addEvent.sendObjectName = Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent); 
			}


			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::ON_EFFECT_SOUND;
				addEvent.sendObjectName = Object()->GetName();
				
				MUSIC_KIND sendData = MUSIC_KIND::EFFECT_WIND;
				addEvent.sendObjectData.uintValue = (UINT)sendData;

				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
		}
		else if (Object()->GetName() == L"EventLightVoluemDown")
		{
			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::INSIDE_LIGHT;
			addEvent.sendObjectName = Object()->GetName();
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
		else if (Object()->GetName() == L"EventLightVoluemUp")
		{
			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::OUTSIDE_LIGHT;
				addEvent.sendObjectName = Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}

			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::ON_EFFECT_SOUND;
				addEvent.sendObjectName = Object()->GetName();

				MUSIC_KIND sendData = MUSIC_KIND::EFFECT_THUNDER;
				addEvent.sendObjectData.uintValue = (UINT)sendData;

				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
		}
	}
}

