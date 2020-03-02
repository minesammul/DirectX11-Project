#include "stdafx.h"
#include "SSN002PlayerScript.h"

#include "PlayerIdleState.h"
#include "SSN005NavScript.h"
#include "EventQueueMgr.h"

CSSN002PlayerScript::CSSN002PlayerScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT),
	PLAYER_MOVE_SPEED(300.f),
	PLAYER_ROLL_SPEED(600.f)
{
	mPlayerMaxHP = 2;
	mPlayerHP = mPlayerMaxHP;
	mPlayerMaxSP = 10;
	mPlayerSP = mPlayerMaxSP;
	mIsHit = false;
	mIsDead = false;
}


CSSN002PlayerScript::~CSSN002PlayerScript()
{
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

		for (int index = 0; index < attackBox->GetScripts().size(); index++)
		{
			if (attackBox->GetScripts()[index]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN008ATTACKBOXSCRIPT)
			{
				mAttackBoxScript = attackBox->GetScripts()[index];
				break;
			}
		}
	}


	{
		GameEventComponent addEvent;
		addEvent.eventType = GAME_EVENT_TYPE::PLAYER_HP_UPDATE;
		addEvent.sendObjectName = Object()->GetName();
		CEventQueueMgr::GetInst()->AddEvent(addEvent);
	}

	mPlayerState = PlayerIdleState::GetInstance();
	mPlayerState->Init(this);
}

void CSSN002PlayerScript::update()
{
	{
		if (mPlayerHP <= 0)
		{
			mIsDead = true;
		}
	}

	{
		if (mIsDead == false)
		{
			vector<CGameObject*> findBody;
			CSceneMgr::GetInst()->FindGameObject(L"MainCameraBody", findBody);

			Vec3 cameraBodyRotate = findBody[0]->Transform()->GetLocalRot();
			Vec3 playerRotate = Transform()->GetLocalRot();
			playerRotate.y = cameraBodyRotate.y;

			Transform()->SetLocalRot(playerRotate);
		}
	}


	{
		for (int index = 0; index < Object()->GetChild().size(); index++)
		{
			vector<CScript*> childScript = Object()->GetChild()[index]->GetScripts();

			for (int scriptIndex = 0; scriptIndex < childScript.size(); scriptIndex++)
			{
				if (childScript[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN005NAVSCRIPT)
				{
					mIsMovable = dynamic_cast<CSSN005NavScript*>(childScript[scriptIndex])->GetNavCollision();
					mBeforePlayerPosition = dynamic_cast<CSSN005NavScript*>(childScript[scriptIndex])->GetBeforePosition();
					break;
				}
			}
		}
	}


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
