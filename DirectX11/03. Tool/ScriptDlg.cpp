// ScriptDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ScriptDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <ScriptMgr.h>
#include <Script.h>


// CScriptDlg 대화 상자

IMPLEMENT_DYNAMIC(CScriptDlg, CDialogEx)



CScriptDlg::CScriptDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_SCRIPTDLG, pParent)
{

}

CScriptDlg::~CScriptDlg()
{
}

void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlScript);
	DDX_Control(pDX, IDC_COMBO1, m_cbScript);
}

void CScriptDlg::init(CGameObject * _pTarget)
{
	vector<wstring> vecName;
	CScriptMgr::GetScriptInfo(vecName);

	for (UINT i = 0; i < vecName.size(); ++i)
	{
		m_cbScript.AddString(vecName[i].c_str());
	}	
}

void CScriptDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	m_ctrlScript.DeleteAllItems();

	vector<CScript*>& vecScript = _pTarget->GetScripts();

	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		CString strName = CScriptMgr::GetScriptName(vecScript[i]);
		m_ctrlScript.InsertItem(i, strName);
	}
}


BEGIN_MESSAGE_MAP(CScriptDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CScriptDlg::OnBtnAddScript)
END_MESSAGE_MAP()


// CScriptDlg 메시지 처리기


void CScriptDlg::OnBtnAddScript()
{
	CString strScriptName;
	int iSel = m_cbScript.GetCurSel();
	m_cbScript.GetLBText(iSel, strScriptName);

	CScript* pNewScript = CScriptMgr::GetScript(strScriptName.GetBuffer());
	GetTarget()->AddComponent(pNewScript);
}