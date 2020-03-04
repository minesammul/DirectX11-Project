#include "stdafx.h"
#include "SSN002PlayerScript.h"

#include "PlayerIdleState.h"
#include "SSN005NavScript.h"
#include "EventQueueMgr.h"
#include "FunctionMgr.h"
#include "SSN008AttackBoxScript.h"

CSSN002PlayerScript::CSSN002PlayerScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT),
	PLAYER_MOVE_SPEED(300.f),
	PLAYER_ROLL_SPEED(600.f)
{

}


CSSN002PlayerScript::~CSSN002PlayerScript()
{
}

void CSSN002PlayerScript::CheckDie()
{
	if (mPlayerHP <= 0)
	{
		mIsDead = true;
	}
}

void CSSN002PlayerScript::LookAtFront()
{
	if (mIsDead == false)
	{
		CGameObject* mainCameraBody = CFunctionMgr::GetInst()->FindObject(L"MainCameraBody");

		Vec3 cameraBodyRotate = mainCameraBody->Transform()->GetLocalRot();
		Vec3 playerRotate = Transform()->GetLocalRot();
		playerRotate.y = cameraBodyRotate.y;

		Transform()->SetLocalRot(playerRotate);
	}
}

void CSSN002PlayerScript::CheckMovable()
{
	for (int index = 0; index < Object()->GetChild().size(); index++)
	{
		CSSN005NavScript* navScript = dynamic_cast<CSSN005NavScript*>(CFunctionMgr::GetInst()->FindScript(Object()->GetChild()[index]->GetName(), SCRIPT_TYPE::SSN005NAVSCRIPT));
		if (navScript != nullptr)
		{
			mIsMovable = navScript->GetNavCollision();
			mBeforePlayerPosition = navScript->GetBeforePosition();
			break;
		}
	}
}

void CSSN002PlayerScript::start()
{
	{
		CGameObject* attackBox = nullptr;
		for (int index = 0; index < Object()->GetChild().size(); index++)
		{
			CLayer* attackBoxLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"AttackBox");
			if (Object()->GetChild()[index]->GetLayerIdx() == attackBoxLayer->GetLayerIdx())
			{
				attackBox = Object()->GetChild()[index];
				break;
			}
		}


		mAttackBoxScript = dynamic_cast<CSSN008AttackBoxScript*>(CFunctionMgr::GetInst()->FindScript(attackBox->GetName(), SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT));
	}


	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::PLAYER_HP_UPDATE;
		addEvent.sendObjectName = Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	mPlayerMaxHP = 2;
	mPlayerHP = mPlayerMaxHP;
	mPlayerMaxSP = 10;
	mPlayerSP = mPlayerMaxSP;
	mIsHit = false;
	mIsDead = false;

	mPlayerState = PlayerIdleState::GetInstance();
	mPlayerState->Init(this);
}

void CSSN002PlayerScript::update()
{
	CheckDie();

	LookAtFront();

	CheckMovable();

	mPlayerState->Update(this);
}

void CSSN002PlayerScript::SetState(PlayerState * state)
{
	mPlayerState = state;
}

void CSSN002PlayerScript::RestoreSP()
{
	static float deltaTime = 0.f;

	if (mPlayerSP < mPlayerMaxSP)
	{
		deltaTime += CTimeMgr::GetInst()->GetDeltaTime();

		if (deltaTime > 1.f)
		{
			deltaTime = 0.f;
			mPlayerSP += 1;

			GameEventComponent addEvent;
			addEvent.eventType = GAME_EVENT_TYPE::PLAYER_SP_UPDATE;
			addEvent.sendObjectName = Object()->GetName();
			CEventQueueMgr::GetInst()->AddEvent(addEvent);
		}
	}
}

void CSSN002PlayerScript::UseSP(int useSPValue)
{
	mPlayerSP -= useSPValue;

	GameEventComponent addEvent;
	addEvent.eventType = GAME_EVENT_TYPE::PLAYER_SP_UPDATE;
	addEvent.sendObjectName = Object()->GetName();
	CEventQueueMgr::GetInst()->AddEvent(addEvent);
}

bool CSSN002PlayerScript::CanUseSP(int useSPValue)
{
	if (useSPValue > mPlayerSP)
	{
		return false;
	}

	return true;
}
