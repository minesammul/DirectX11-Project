#pragma once
#include <Script.h>

enum class ITEM_TYPE
{
	KIND,
	IMAGE,
	EFFECT,
	END
};

class ItemComponent;

class CItemScript : public CScript
{
private:
	ItemComponent* itemComponents[(UINT)ITEM_TYPE::END];
	CResPtr<CMaterial>  m_pOriginMtrl;
	CResPtr<CMaterial>  m_pCloneMtrl;

public:
	CItemScript();
	~CItemScript();

public:
	virtual void awake();
	virtual void start();
	virtual void update();


	void Play();

	CResPtr<CMaterial>& GetItemMtrl() { return m_pCloneMtrl; }
};

