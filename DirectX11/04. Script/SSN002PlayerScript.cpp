#include "stdafx.h"
#include "SSN002PlayerScript.h"

#include "PlayerIdleState.h"
#include "SSN005NavScript.h"

CSSN002PlayerScript::CSSN002PlayerScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN002PLAYERSCRIPT),
	PLAYER_MOVE_SPEED(10.f)
{

}


CSSN002PlayerScript::~CSSN002PlayerScript()
{
}

void CSSN002PlayerScript::start()
{
	playerState = PlayerIdleState::GetInstance();
	playerState->Init(this);
}

void CSSN002PlayerScript::update()
{
	{
		vector<CGameObject*> findBody;
		CSceneMgr::GetInst()->FindGameObject(L"MainCameraBody", findBody);

		Vec3 cameraBodyRotate = findBody[0]->Transform()->GetLocalRot();
		Vec3 playerRotate = Transform()->GetLocalRot();
		playerRotate.y = cameraBodyRotate.y;

		Transform()->SetLocalRot(playerRotate);
	}


	{
		for (int index = 0; index < Object()->GetChild().size(); index++)
		{
			vector<CScript*> childScript = Object()->GetChild()[index]->GetScripts();

			for (int scriptIndex = 0; scriptIndex < childScript.size(); scriptIndex++)
			{
				if (childScript[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::SSN005NAVSCRIPT)
				{
					isMovable = dynamic_cast<CSSN005NavScript*>(childScript[scriptIndex])->GetNavCollision();
					beforePlayerPosition = dynamic_cast<CSSN005NavScript*>(childScript[scriptIndex])->GetBeforePosition();
					break;
				}
			}
		}
	}


	playerState->Update(this);
}

void CSSN002PlayerScript::SetState(PlayerState * state)
{
	playerState = state;
}
