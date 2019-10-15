#include "stdafx.h"
#include "PlayerActionStateMove.h"
#include "PlayerActionStateIdle.h"

PlayerActionStateMove::PlayerActionStateMove()
{
}


PlayerActionStateMove::~PlayerActionStateMove()
{
}

void PlayerActionStateMove::FindAnimation(CPlayerScript * player)
{
	//�ӽ��ڵ�. ĳ���Ͱ� ���� �ִϸ��̼� key���� ���� �ڽ�Ƭ�� �б����� ���� �޶�����.
	if (player->Object()->Animator2D()->GetAnimList().find(L"adventure_move") !=
		player->Object()->Animator2D()->GetAnimList().end())
	{
		CAnimation2D* curAnimation = player->Object()->Animator2D()->GetAnimList().find(L"adventure_move")->second;

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

void PlayerActionStateMove::ActionState(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_HOLD)
	{
		Vec3 playerPosition = player->Object()->Transform()->GetLocalPos();
		playerPosition.x -= player->GetMoveSpeed()*DT;
		player->Object()->Transform()->SetLocalPos(playerPosition);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_HOLD)
	{
		Vec3 playerPosition = player->Object()->Transform()->GetLocalPos();
		playerPosition.x += player->GetMoveSpeed()*DT;
		player->Object()->Transform()->SetLocalPos(playerPosition);
	}
}

void PlayerActionStateMove::TransactionState(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_AWAY ||
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_AWAY)
	{
		player->SetActionState(PlayerActionStateIdle::GetInstance());
	}
}

void PlayerActionStateMove::Update(CPlayerScript * player)
{
	FindAnimation(player);
	TransactionState(player);
	ActionState(player);
}
