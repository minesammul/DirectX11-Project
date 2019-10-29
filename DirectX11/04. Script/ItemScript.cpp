#include "stdafx.h"
#include "ItemScript.h"
#include "ItemComponent.h"
#include "ItemKind.h"
#include "ItemEffect.h"
#include "ItemImage.h"

#include "EventQueueScript.h"

CItemScript::CItemScript():
	CScript((UINT)SCRIPT_TYPE::ITEMSCRIPT)
{
	//�ӽ��ڵ� ���߿� ������ Component�� �ڽ��� Ÿ���� �˰��Ѵ�.
	//�׸��� Player���� item�� Component�� �����ؼ� �Ѱ��� �� �ֵ��� �Ѵ�.
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		itemComponents[itemComponentIndex] = nullptr;
	}

	itemComponents[(UINT)ITEM_TYPE::KIND] = new ItemKind;
	itemComponents[(UINT)ITEM_TYPE::IMAGE] = new ItemImage;
	itemComponents[(UINT)ITEM_TYPE::EFFECT] = new ItemEffect;

	activeAttack = false;
	activeAttackTime = 0.f;
	isHit = false;
}


CItemScript::~CItemScript()
{
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] != nullptr)
		{
			delete itemComponents[itemComponentIndex];
			itemComponents[itemComponentIndex] = nullptr;
		}
	}
}

void CItemScript::awake()
{
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}

		itemComponents[itemComponentIndex]->Init(this);
	}
}

void CItemScript::start()
{
	m_pOriginMtrl = MeshRender()->GetSharedMaterial();
	m_pCloneMtrl = MeshRender()->GetCloneMaterial();
}

void CItemScript::update()
{
	//�ӽ��ڵ� ���߿� �÷��̾�� ������ �� �ֵ��� �Ѵ�.
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_TAB)
	{
		Play();
		activeAttack = true;
	}

	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}

		itemComponents[itemComponentIndex]->Update(this);
	}

	if (activeAttack == true)
	{
		activeAttackTime += DT;
		if (activeAttackTime > 0.2)
		{
			activeAttack = false;
		}
	}
	else
	{
		activeAttackTime = 0.f;
	}

	/*MeshRender()->SetMaterial(m_pCloneMtrl);
	if (nullptr != m_pCloneMtrl)
	{
		CResPtr<CTexture> itemTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Item\\BasicShortSword\\BasicShortSword.png");
		m_pCloneMtrl->SetData(SHADER_PARAM::TEX_0, &itemTexture);
	}*/
}

void CItemScript::OnCollision(CCollider2D * _pOther)
{
	if (activeAttack == true)
	{
		EVENT_PACKET packet;
		packet.eventSendTargetID = _pOther->Object()->GetID();
		packet.eventType = EVENTQUEUE_TYPE::ATTACK;
		CEventQueueScript::GetInstance()->EnqueueEvent(packet);
		
		hitPosition = _pOther->Object()->Transform()->GetLocalPos();

		activeAttack = false;
		isHit = true;
	}
}

void CItemScript::Play()
{
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}
		itemComponents[itemComponentIndex]->Action(this);
	}
}

ItemKind * CItemScript::GetItemKind(void)
{
	ItemKind* itemKind = dynamic_cast<ItemKind*>(itemComponents[(UINT)ITEM_TYPE::KIND]);
	return itemKind;
}
