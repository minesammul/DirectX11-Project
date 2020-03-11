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
				addEvent.eventType = GAME_EVENT_TYPE::PARTICLE_RAIN_START;
				addEvent.sendObjectName = Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}


			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::ON_EFFECT_SOUND_WIND;
				addEvent.sendObjectName = Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
		}
		else if (Object()->GetName() == L"EventLightVoluemDown")
		{
			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::INSIDE_LIGHT;
				addEvent.sendObjectName = Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}

			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::OFF_INOUTSIDE_MESH;
				addEvent.sendObjectName = Object()->GetName();
				addEvent.receiveObjectName = L"ToInside1";
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}

			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::LIGHT_MOVE;
				addEvent.sendObjectName = Object()->GetName();

				SendData inputX;
				inputX.floatValue = 6000.f;
				addEvent.sendObjectData.push_back(inputX);

				SendData inputY;
				inputY.floatValue = 0.f;
				addEvent.sendObjectData.push_back(inputY);

				SendData inputZ;
				inputZ.floatValue = 0.f;
				addEvent.sendObjectData.push_back(inputZ);

				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
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
				addEvent.eventType = GAME_EVENT_TYPE::ON_EFFECT_SOUND_THUNDER;
				addEvent.sendObjectName = Object()->GetName();
				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}

			{
				GameEventComponent addEvent;
				addEvent.eventType = GAME_EVENT_TYPE::LIGHT_MOVE;
				addEvent.sendObjectName = Object()->GetName();

				SendData inputX;
				inputX.floatValue = 6000.f;
				addEvent.sendObjectData.push_back(inputX);

				SendData inputY;
				inputY.floatValue = 0.f;
				addEvent.sendObjectData.push_back(inputY);

				SendData inputZ;
				inputZ.floatValue = 0.f;
				addEvent.sendObjectData.push_back(inputZ);

				CEventQueueMgr::GetInst()->AddEvent(addEvent);
			}
		}
	}
}

