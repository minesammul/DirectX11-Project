#include "stdafx.h"
#include "PlayerActionStateDash.h"
#include "PlayerActionStateIdle.h"
#include "BottomWallCollisionScript.h"
#include "RightBottomWallCollisionScript.h"
#include "LeftBottomWallCollisionScript.h"
#include "TopWallCollisionScript.h"
#include "RightWallCollisionScript.h"
#include "LeftWallCollisionScript.h"


PlayerActionStateDash::PlayerActionStateDash()
{
}


PlayerActionStateDash::~PlayerActionStateDash()
{
}

void PlayerActionStateDash::FindAnimation(CPlayerScript * player)
{
	//임시코드. 캐릭터가 지닌 애니메이션 key값은 추후 코스튬의 분기점에 따라 달라진다.
	if (player->Object()->Animator2D()->GetAnimList().find(L"adventure_jump") !=
		player->Object()->Animator2D()->GetAnimList().end())
	{
		CAnimation2D* curAnimation = player->Object()->Animator2D()->GetAnimList().find(L"adventure_jump")->second;

		if (player->Object()->Animator2D()->GetCurAnim()->GetID() != curAnimation->GetID())
		{
			player->Object()->Animator2D()->SetCurAnim(curAnimation);
		}
	}

	if (player->Object()->Animator2D()->GetCurAnim()->IsPlay() == false)
	{
		player->Object()->Animator2D()->GetCurAnim()->Play();
	}
}

void PlayerActionStateDash::TransactionState(CPlayerScript * player)
{
	ChangeDashToIdle(player);
}

void PlayerActionStateDash::ChangeDashToIdle(CPlayerScript * player)
{
	CheckDashDistance(player);
	CheckDashWithWallCollision(player);
}

void PlayerActionStateDash::CheckDashDistance(CPlayerScript * player)
{
	Vec3 playerPosition = player->Object()->Transform()->GetLocalPos();
	playerPosition.x += dashDirection.x*DASH_POWER*DT;
	playerPosition.y += dashDirection.y*DASH_POWER*DT;
	player->Object()->Transform()->SetLocalPos(playerPosition);

	XMVECTOR nowDistance = XMVector3Length(startPosition - playerPosition);
	if (nowDistance.vector4_f32[0] > DASH_DISTANCE)
	{
		player->SetActionState(PlayerActionStateIdle::GetInstance());
	}
}

void PlayerActionStateDash::CheckDashWithWallCollision(CPlayerScript * player)
{
	bool isCollision = false;

	vector<CGameObject*> childObjects = player->Object()->GetChild();
	for (int objectIndex = 0; objectIndex < childObjects.size(); objectIndex++)
	{
		vector<CScript*> childScripts = childObjects[objectIndex]->GetScripts();
		for (int scriptIndex = 0; scriptIndex < childScripts.size(); scriptIndex++)
		{
			switch ((UINT)childScripts[scriptIndex]->GetScriptType())
			{
			case (UINT)SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT:
			{
				CBottomWallCollisionScript* script = dynamic_cast<CBottomWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::LEFTBOTTOMWALLCOLLISIONSCRIPT:
			{
				CLeftBottomWallCollisionScript* script = dynamic_cast<CLeftBottomWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT:
			{
				CRightBottomWallCollisionScript* script = dynamic_cast<CRightBottomWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::LEFTWALLCOLLISIONSCRIPT:
			{
				CLeftWallCollisionScript* script = dynamic_cast<CLeftWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::RIGHTWALLCOLLISIONSCRIPT:
			{
				CRightWallCollisionScript* script = dynamic_cast<CRightWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT:
			{
				CTopWallCollisionScript* script = dynamic_cast<CTopWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			}

			if (isCollision == true)
			{
				player->SetActionState(PlayerActionStateIdle::GetInstance());
			}
		}
	}
}

void PlayerActionStateDash::Update(CPlayerScript * player)
{
	FindAnimation(player);
	TransactionState(player);
}
