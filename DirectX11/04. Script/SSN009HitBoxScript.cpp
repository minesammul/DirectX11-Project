#include "stdafx.h"
#include "SSN009HitBoxScript.h"

#include "SSN008AttackBoxScript.h"
#include "EventQueueMgr.h"
#include "FunctionMgr.h"

CSSN009HitBoxScript::CSSN009HitBoxScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN009HITBOXSCRIPT)
{
}


CSSN009HitBoxScript::~CSSN009HitBoxScript()
{
}

void CSSN009HitBoxScript::OnCollision(CCollider3D * _pOther)
{
	CSSN008AttackBoxScript* attackBoxScript = dynamic_cast<CSSN008AttackBoxScript*>(CFunctionMgr::GetInst()->FindScript(_pOther->Object()->GetName(), SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT));
	if (attackBoxScript != nullptr)
	{
		bool isAttackBoxActive = attackBoxScript->GetActiveCollision();
		bool isAttacked = attackBoxScript->GetAttackted();

		if (isAttackBoxActive == true && isAttacked == false)
		{
			attackBoxScript->SetAttackted(true);

			GameEventComponent hitEvent;
			hitEvent.eventType = GAME_EVENT_TYPE::HIT;
			hitEvent.sendObjectName = _pOther->Object()->GetName();
			hitEvent.receiveObjectName = Object()->GetParent()->GetName();

			CEventQueueMgr::GetInst()->AddEvent(hitEvent);
		}
	}
}