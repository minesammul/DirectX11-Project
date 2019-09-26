// MaterialDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MaterialDlg.h"
#include "afxdialogex.h"

#include "ListDlg.h"
#include <ResMgr.h>
#include <Shader.h>
// CMaterialDlg 대화 상자

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialogEx)

CMaterialDlg::CMaterialDlg(CWnd* pParent /*=nullptr*/)
	: CResInfoDlg(IDD_MTRLDLG, pParent)
{

}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editShaderName);
}

void CMaterialDlg::SetResource(CResource * _pRes)
{
	CResInfoDlg::SetResource(_pRes);

	CResPtr<CShader> pShader = ((CMaterial*)_pRes)->GetShader();
	if (nullptr == pShader)
		m_editShaderName.SetWindowTextW(L"");
	else
		m_editShaderName.SetWindowTextW(pShader->GetName().c_str());
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMaterialDlg::OnSelShader)
END_MESSAGE_MAP()


// CMaterialDlg 메시지 처리기


void CMaterialDlg::OnSelShader()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources(RES_TYPE::SHADER);

	vector<CString> vecFileName;
	vector<CString> vecResName;

	for (const auto& pair : mapRes)
	{
		vecFileName.push_back(CPathMgr::GetFileName(pair.second->GetName().c_str()));
		vecResName.push_back(pair.second->GetName().c_str());
	}

	CListDlg dlg(L"Shader", vecFileName);
	int iRet = dlg.DoModal();

	if (IDOK == iRet)
	{
		CString strSelect = dlg.GetSelectItem();
		CResPtr<CShader> pShader = CResMgr::GetInst()->FindRes<CShader>(strSelect.GetBuffer());

		CResPtr<CMaterial> pMtrl = (CMaterial*)GetRes();
		pMtrl->SetShader(pShader);

		if (nullptr == pShader)
			m_editShaderName.SetWindowTextW(L"");
		else
			m_editShaderName.SetWindowTextW(pShader->GetName().c_str());
	}
}
