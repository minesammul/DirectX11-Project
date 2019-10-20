#include "stdafx.h"
#include "ItemScript.h"
#include "ItemComponent.h"
#include "ItemKind.h"
#include "ItemEffect.h"
#include "ItemImage.h"

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
	}

	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}

		itemComponents[itemComponentIndex]->Update(this);
	}

	/*MeshRender()->SetMaterial(m_pCloneMtrl);
	if (nullptr != m_pCloneMtrl)
	{
		CResPtr<CTexture> itemTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Item\\BasicShortSword\\BasicShortSword.png");
		m_pCloneMtrl->SetData(SHADER_PARAM::TEX_0, &itemTexture);
	}*/
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
