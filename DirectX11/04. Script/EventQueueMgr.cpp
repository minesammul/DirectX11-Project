#include "stdafx.h"
#include "EventQueueMgr.h"


CEventQueueMgr::CEventQueueMgr()
{
}


CEventQueueMgr::~CEventQueueMgr()
{
}

void CEventQueueMgr::AddEvent(GameEventComponent addEvent)
{
	events.push(addEvent);
}
