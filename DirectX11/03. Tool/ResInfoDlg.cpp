#include "stdafx.h"
#include "ResInfoDlg.h"


CResInfoDlg::CResInfoDlg(UINT _iResID, CWnd* _pParent)
	: CDialogEx(_iResID, _pParent)
	, m_pResource(nullptr)
{
}


CResInfoDlg::~CResInfoDlg()
{
}


void CResInfoDlg::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;
	CDialogEx::PostNcDestroy();
}


void CResInfoDlg::OnOK() {}
void CResInfoDlg::OnCancel() {}