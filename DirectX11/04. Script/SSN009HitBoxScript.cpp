#include "stdafx.h"
#include "SSN009HitBoxScript.h"

#include "SSN008AttackBoxScript.h"
#include "EventQueueMgr.h"

CSSN009HitBoxScript::CSSN009HitBoxScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN009HITBOXSCRIPT)
{
}


CSSN009HitBoxScript::~CSSN009HitBoxScript()
{
}

void CSSN009HitBoxScript::OnCollision(CCollider3D * _pOther)
{
	for (int index = 0; index < _pOther->Object()->GetScripts().size(); index++)
	{
		if (_pOther->Object()->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT)
		{
			bool isAttackBoxActive = dynamic_cast<CSSN008AttackBoxScript*>(_pOther->Object()->GetScripts()[index])->GetActiveCollision();
			bool isAttacked = dynamic_cast<CSSN008AttackBoxScript*>(_pOther->Object()->GetScripts()[index])->GetAttackted();

			if (isAttackBoxActive == true && isAttacked == false)
			{
				dynamic_cast<CSSN008AttackBoxScript*>(_pOther->Object()->GetScripts()[index])->SetAttackted(true);

				GameEventComponent hitEvent;
				hitEvent.eventType = GAME_EVENT_TYPE::HIT;
				hitEvent.sendObjectName = _pOther->Object()->GetName();
				hitEvent.receiveObjectName = Object()->GetParent()->GetName();

				CEventQueueMgr::GetInst()->AddEvent(hitEvent);
			}
			break;
		}
	}

}