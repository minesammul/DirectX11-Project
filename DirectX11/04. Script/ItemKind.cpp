#include "stdafx.h"
#include "ItemKind.h"
#include "ItemKindStrategy.h"
#include "ItemSwordKindStrategy.h"
#include "PlayerScript.h"

ItemKind::ItemKind()
{
	//�ӽ��ڵ� ���߿� �÷��̾����׼� �޾ƿ;��Ѵ�.
	this->itemKindStrategy = new ItemSwordKindStrategy;
	itemDirection = Vec3(0.f, 1.f, 0.f);
	itemRotate = Vec3(0.f, 0.f, 0.f);
}


ItemKind::~ItemKind()
{
	if (this->itemKindStrategy != nullptr)
	{
		delete this->itemKindStrategy;
		this->itemKindStrategy = nullptr;
	}
}

void ItemKind::Action(CItemScript* item)
{
	itemPosition = item->Object()->Transform()->GetLocalPos();
	this->itemKindStrategy->Action(this);
	item->Object()->Transform()->SetLocalPos(itemPosition);
}

void ItemKind::Init(CItemScript * item)
{
}

void ItemKind::Update(CItemScript * item)
{
	vector<CScript*> playerScripts = item->Object()->GetParent()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < playerScripts.size(); scriptIndex++)
	{
		if (playerScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLAYERSCRIPT)
		{
			CPlayerScript* playerScript = dynamic_cast<CPlayerScript*>(playerScripts[scriptIndex]);
			mouseDirection = playerScript->GetMouseDirection();
		}
	}

	item->Object()->GetParent()->Transform()->SetLocalRot(itemAxisRotate);
	item->Object()->Transform()->SetLocalRot(itemRotate);

	this->itemKindStrategy->Update(this);
}
