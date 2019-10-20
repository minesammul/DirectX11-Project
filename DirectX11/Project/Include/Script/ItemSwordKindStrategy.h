#pragma once
#include "ItemKindStrategy.h"

enum class SWORD_STATE
{
	UP,
	DOWN,
	END
};

class ItemSwordKindStrategy : public ItemKindStrategy
{
private:
	SWORD_STATE swordState;

public:
	ItemSwordKindStrategy();
	~ItemSwordKindStrategy();

public:
	// ItemKindStrategy��(��) ���� ��ӵ�
	virtual void Action(ItemKind* itemKind) override;

	// ItemKindStrategy��(��) ���� ��ӵ�
	virtual void Update(ItemKind* itemKind) override;
};

