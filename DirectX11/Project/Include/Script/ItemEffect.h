#pragma once
#include "ItemComponent.h"
class ItemEffect : public ItemComponent
{
private:
	CResPtr<CPrefab> effectPrefab;

public:
	ItemEffect();
	~ItemEffect();

	// ItemComponent��(��) ���� ��ӵ�
	virtual void Init(CItemScript * item) override;
	virtual void Action(CItemScript * item) override;
	virtual void Update(CItemScript * item) override;
};

