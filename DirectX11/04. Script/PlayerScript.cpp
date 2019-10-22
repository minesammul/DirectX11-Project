#include "stdafx.h"
#include "PlayerScript.h"
#include <Camera.h>

#include "PlayerActionState.h"
#include "PlayerActionStateIdle.h"
#include "PlayerActionStateMove.h"
#include "PlayerActionStateJump.h"
#include "PlayerActionStateDash.h"
#include "PlayerActionStateSit.h"

#include "PlatformRightCollisionScript.h"
#include "PlatformLeftCollisionScript.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
{
	//actionState = new PlayerActionStateIdle
	actionState = PlayerActionStateIdle::GetInstance();
	moveSpeed = 200.f;
	moveDirection = Vec3(1.f, 0.f, 0.f);
}

CPlayerScript::~CPlayerScript()
{
	if (PlayerActionStateIdle::GetInstance() != nullptr)
	{
		actionState = PlayerActionStateIdle::GetInstance();
		delete actionState;
	}

	if (PlayerActionStateJump::GetInstance() != nullptr)
	{
		actionState = PlayerActionStateJump::GetInstance();
		delete actionState;
	}

	if (PlayerActionStateMove::GetInstance() != nullptr)
	{
		actionState = PlayerActionStateMove::GetInstance();
		delete actionState;
	}

	if (PlayerActionStateDash::GetInstance() != nullptr)
	{
		actionState = PlayerActionStateDash::GetInstance();
		delete actionState;
	}

	if (PlayerActionStateSit::GetInstance() != nullptr)
	{
		actionState = PlayerActionStateSit::GetInstance();
		delete actionState;
	}
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

void CPlayerScript::CalculationMouseDirection()
{
	Vec3 playerPosition = Object()->Transform()->GetLocalPos();

	POINT mousePosition = CKeyMgr::GetInst()->GetMousePos();

	vector<CCamera*> curSceneCameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	CCamera* camera = nullptr;
	for (int cameraIndex = 0; cameraIndex < curSceneCameras.size(); cameraIndex++)
	{
		CCamera* curCamera = curSceneCameras[cameraIndex];
		if (curCamera->IsValiedLayer(Object()->GetLayerIdx()) == true)
		{
			camera = curCamera;
			break;
		}
	}

	XMVECTOR sceneMousePosition = CSceneMgr::GetInst()->CalculationSceneMousePosition(
		mousePosition,
		camera
	);

	mouseDirection = sceneMousePosition - playerPosition;
	mouseDirection = XMVector3Normalize(mouseDirection);
}

void CPlayerScript::start()
{
}

void CPlayerScript::update()
{
	actionState->Update(this);
	CalculationMoveDirection();
	CalculationMouseDirection();

	if (mouseDirection.x > 0)
	{
		int inversOff = 0;
		Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &inversOff);
	}
	else
	{
		int inversON = 1;
		Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &inversON);
	}
}
