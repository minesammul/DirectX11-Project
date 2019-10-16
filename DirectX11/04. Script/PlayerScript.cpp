#include "stdafx.h"
#include "PlayerScript.h"
#include "PlayerActionState.h"
#include "PlayerActionStateIdle.h"
#include "PlayerActionStateMove.h"

#include "PlatformRightCollisionScript.h"
#include "PlatformLeftCollisionScript.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
{
	actionState = new PlayerActionStateIdle;
	moveSpeed = 200.f;
	moveDirection = Vec3(1.f, 0.f, 0.f);
}

CPlayerScript::~CPlayerScript()
{
	delete actionState;
}

void CPlayerScript::CalculationMoveDirection()
{
	vector<CGameObject*> childObject = Object()->GetChild();
	bool isFind = false;
	for (int childIndex = 0; childIndex < childObject.size(); childIndex++)
	{
		vector<CScript*> childScripts = childObject[childIndex]->GetScripts();
		for (int scriptIndex = 0; scriptIndex < childScripts.size(); scriptIndex++)
		{
			if (childScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLATFORMRIGHTCOLLISIONSCRIPT)
			{
				CPlatformRightCollisionScript* platformRightCollisionScript = dynamic_cast<CPlatformRightCollisionScript*>(childScripts[scriptIndex]);
				if (platformRightCollisionScript->GetCollision())
				{
					moveDirection = platformRightCollisionScript->GetCollisionMoveDirection();
					moveDirection = XMVector3Normalize(moveDirection);
					moveDirection.x *= -1;
					moveDirection.y *= -1;
					moveDirection.z *= -1;
					isFind = true;
					break;
				}
			}
			if (childScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLATFORMLEFTCOLLISIONSCRIPT)
			{
				CPlatformLeftCollisionScript* platformLeftCollisionScript = dynamic_cast<CPlatformLeftCollisionScript*>(childScripts[scriptIndex]);
				if (platformLeftCollisionScript->GetCollision())
				{
					moveDirection = platformLeftCollisionScript->GetCollisionMoveDirection();
					moveDirection = XMVector3Normalize(moveDirection);
					moveDirection.x *= -1;
					moveDirection.y *= -1;
					moveDirection.z *= -1;
					isFind = true;
					break;
				}
			}
		}

		if (isFind == true)
		{
			break;
		}
	}
	if (isFind == false)
	{
		moveDirection = Vec3(1.f, 0.f, 0.f);
	}
}

void CPlayerScript::start()
{
}

void CPlayerScript::update()
{
	actionState->Update(this);
	CalculationMoveDirection();
}
