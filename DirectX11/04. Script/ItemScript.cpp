#include "stdafx.h"
#include "ItemScript.h"
#include "ItemComponent.h"
#include "ItemKind.h"
#include "ItemEffect.h"
#include "ItemImage.h"

CItemScript::CItemScript():
	CScript((UINT)SCRIPT_TYPE::ITEMSCRIPT)
{
	//임시코드 나중에 각각의 Component가 자신의 타입을 알게한다.
	//그리고 Player에서 item의 Component를 설정해서 넘겨줄 수 있도록 한다.
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
	//임시코드 나중에 플레이어에서 조작할 수 있도록 한다.
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
