#include "stdafx.h"
#include "Script.h"

#include "EventMgr.h"

CScript::CScript(UINT _iType)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_iScriptType(_iType)
{
}

CScript::~CScript()
{
}

void CScript::Instantiate(CResPtr<CPrefab>& _pPrefab, const Vec3 & _vPos, const wstring & _strLayerName)
{	
	CGameObject* pClone = _pPrefab->Instantiate();
	pClone->Transform()->SetLocalPos(_vPos);
	CreateObject(pClone);	
}


// ===========
// Event Ã³¸®
// ===========
void CScript::AddChild(CGameObject * _pChildObject)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::ADD_CHILD;
	e.lParam = (INT_PTR)Object();
	e.wParam = (INT_PTR)_pChildObject;

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::ClearChild(UINT _iChildIdx)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::CLEAR_CHILD;
	e.lParam = (INT_PTR)Object();
	e.wParam = (INT_PTR)_iChildIdx;

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::ClearParent()
{
	tEvent e = {};

	e.eType = EVENT_TYPE::CLEAR_PARANT;
	e.lParam = (INT_PTR)Object();	

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::CreateObject(CGameObject * _pTarget)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::CREATE_OBJECT;

	e.lParam = (INT_PTR)_pTarget;
	e.wParam = (INT_PTR)_pTarget->GetLayerIdx();

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::DeleteObject(CGameObject * _pTarget)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::DELETE_OBJECT;

	e.lParam = (INT_PTR)_pTarget;	

	CEventMgr::GetInst()->AddEvent(e);
}
