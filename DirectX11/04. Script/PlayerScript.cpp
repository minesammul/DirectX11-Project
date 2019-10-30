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

#include "EventQueueScript.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
{
	actionState = PlayerActionStateIdle::GetInstance();
	moveSpeed = 200.f;
	moveDirection = Vec3(1.f, 0.f, 0.f);

	playerData.maxHp = 100;
	playerData.nowHp = 100;

	isHited = false;
	isCameraFocusPositionFind = false;
	beforeCameraFocusObjectID = 0;
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
	SendPlayerDataToEventQueue();

	CLayer* findLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"CameraFocus");
	cameraFocusLayerIndex = findLayer->GetLayerIdx();
}

void CPlayerScript::update()
{
	actionState->Update(this);
	CalculationMoveDirection();
	CalculationMouseDirection();

	if (mouseDirection.x > 0)
	{
		cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
		int inversOff = 0;
		cloneMtrl->SetData(SHADER_PARAM::INT_0, &inversOff);
	}
	else
	{
		cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
		int inversON = 1;
		cloneMtrl->SetData(SHADER_PARAM::INT_0, &inversON);
	}

	if (isHited == true)
	{
		isHited = false;
		SendPlayerDataToEventQueue();
	}
}

void CPlayerScript::OnCollisionEnter(CCollider2D * _pOther)
{
	int collisionObjectLayerIndex = _pOther->Object()->GetLayerIdx();
	if (cameraFocusLayerIndex == collisionObjectLayerIndex)
	{
		if (beforeCameraFocusObjectID != _pOther->GetID())
		{
			beforeCameraFocusObjectID = _pOther->GetID();
			isCameraFocusPositionFind = true;
			cameraFocusPosition = _pOther->Object()->Transform()->GetLocalPos();
		}
	}
}

void CPlayerScript::OnCollisionExit(CCollider2D * _pOther)
{
	isCameraFocusPositionFind = false;
}

void CPlayerScript::SendPlayerDataToEventQueue(void)
{
	EVENT_PACKET packet;
	packet.eventType = EVENTQUEUE_TYPE::PLAYER_DATA;
	packet.value.push_back(this->playerData.maxHp);
	packet.value.push_back(this->playerData.nowHp);

	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerHpBar", findObject);
	packet.eventSendTargetID = findObject[0]->GetID();

	CEventQueueScript::GetInstance()->EnqueueEvent(packet);
}

void CPlayerScript::PlayerHited(void)
{
	playerData.nowHp -= 1;
	isHited = true;
}
