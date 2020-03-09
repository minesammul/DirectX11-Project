#include "stdafx.h"
#include "SSN015StageEventScript.h"

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
			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::SKY_CHANGE_BATTLE;
			addEvent.sendObjectName = Object()->GetName();
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
		else if (Object()->GetName() == L"EventLightVoluemDown")
		{
			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::LIGHT_VOLUEM_DOWN;
			addEvent.sendObjectName = Object()->GetName();
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
	}
}

