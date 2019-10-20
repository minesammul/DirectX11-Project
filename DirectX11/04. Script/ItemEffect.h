#pragma once
#include "ItemComponent.h"
class ItemEffect : public ItemComponent
{
private:
	CResPtr<CPrefab> effectPrefab;

public:
	ItemEffect();
	~ItemEffect();

	// ItemComponent을(를) 통해 상속됨
	virtual void Init(CItemScript * item) override;
	virtual void Action(CItemScript * item) override;
	virtual void Update(CItemScript * item) override;
};

