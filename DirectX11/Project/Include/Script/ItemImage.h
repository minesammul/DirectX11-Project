#pragma once
#include "ItemComponent.h"
class ItemImage : public ItemComponent
{
public:
	ItemImage();
	~ItemImage();

public:
	// ItemComponent��(��) ���� ��ӵ�
	virtual void Action(CItemScript* item) override;

	// ItemComponent��(��) ���� ��ӵ�
	virtual void Init(CItemScript * item) override;

	// ItemComponent��(��) ���� ��ӵ�
	virtual void Update(CItemScript * item) override;
};

