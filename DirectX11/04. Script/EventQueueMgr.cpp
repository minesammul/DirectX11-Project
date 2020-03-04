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
	mEvents.push(addEvent);
}
