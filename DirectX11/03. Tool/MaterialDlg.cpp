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
	DDX_Control(pDX, IDC_LIST1, listShaderParameterType);
	DDX_Control(pDX, IDC_LIST2, listctrlShaderParameterValue);
}

void CMaterialDlg::SetResource(CResource * _pRes)
{
	CResInfoDlg::SetResource(_pRes);

	CResPtr<CShader> pShader = ((CMaterial*)_pRes)->GetShader();
	if (nullptr == pShader)
		m_editShaderName.SetWindowTextW(L"");
	else
		m_editShaderName.SetWindowTextW(pShader->GetName().c_str());


	listShaderParameterType.ResetContent();
	
	listctrlShaderParameterValue.DeleteAllItems();

	vector<tPramInfo> shaderParameterData = pShader->GetParamInfo();
	int searchTypeCount = shaderParameterData.size();
	for (int index = 0; index < searchTypeCount; index++)
	{
		listShaderParameterType.InsertString(index, shaderParameterData[index].szName);
	}

}

BOOL CMaterialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	listctrlShaderParameterValue.InsertColumn(0, L"Parameter", LVCFMT_CENTER, 65);
	listctrlShaderParameterValue.InsertColumn(1, L"Value", LVCFMT_CENTER, 50);
	return 0;
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMaterialDlg::OnSelShader)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMaterialDlg::OnLbnSelchangeList1)
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


void CMaterialDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int selectIndex = listShaderParameterType.GetCurSel();

	if (selectIndex == -1)
	{
		return;
	}

	CString selectItemName;
	listShaderParameterType.GetText(selectIndex, selectItemName);

	CResPtr<CShader> pShader = ((CMaterial*)CResInfoDlg::GetRes())->GetShader();
	vector<tPramInfo> selectParameter = pShader->GetParamInfo();
	tPramInfo selectParameterData;
	for (int index = 0; index < selectParameter.size(); index++)
	{
		if (selectItemName.Compare(selectParameter[index].szName) == 0)
		{
			selectParameterData = selectParameter[index];
			break;
		}
	}

	listctrlShaderParameterValue.DeleteAllItems();
	//tShaderParam

	CString parameterName = L"";
	int paramterValueCount = 0;


	bool isFloat = true;
	switch (selectParameterData.eType)
	{
	case SHADER_PARAM::INT_0:
		parameterName = L"INT_0";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::INT_1:
		parameterName = L"INT_1";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::INT_2:
		parameterName = L"INT_2";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::INT_3:
		parameterName = L"INT_3";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::FLOAT_0:
		parameterName = L"FLOAT_0";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::FLOAT_1:
		parameterName = L"FLOAT_1";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::FLOAT_2:
		parameterName = L"FLOAT_2";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::FLOAT_3:
		parameterName = L"FLOAT_3";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::VEC2_0:
		parameterName = L"VEC2_0";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC2_1:
		parameterName = L"VEC2_1";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC2_2:
		parameterName = L"VEC2_2";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC2_3:
		parameterName = L"VEC2_3";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC4_0:
		parameterName = L"VEC4_0";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::VEC4_1:
		parameterName = L"VEC4_1";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::VEC4_2:
		parameterName = L"VEC4_2";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::VEC4_3:
		parameterName = L"VEC4_3";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::MAT_0:
		parameterName = L"MAT_0";
		paramterValueCount = 16;
		break;
	case SHADER_PARAM::MAT_1:
		parameterName = L"MAT_1";
		paramterValueCount = 16;
		break;
	case SHADER_PARAM::MAT_2:
		parameterName = L"MAT_2";
		paramterValueCount = 16;
		break;
	case SHADER_PARAM::MAT_3:
		parameterName = L"MAT_3";
		paramterValueCount = 16;
		break;
	default:
		break;
	}

	for (int index = 0; index < paramterValueCount; index++)
	{
		CString inputParameterName = parameterName;
		CString inputParameterNumber;

		int digits10 = 0;
		int digits1 = 0;
		if (index != 0)
		{
			digits10 = (index) / 4;
			digits1 = (index - (digits10*4)) % 4;
		}

		inputParameterNumber.Format(L" %d%d", digits10, digits1);
		inputParameterName += inputParameterNumber;
		listctrlShaderParameterValue.InsertItem(index, inputParameterName);
	}

	if (isFloat == true)
	{
		vector<float> inputShaderParameterValue;
		int iIdx;
		switch (selectParameterData.eType)
		{
		case SHADER_PARAM::FLOAT_0:
		case SHADER_PARAM::FLOAT_1:
		case SHADER_PARAM::FLOAT_2:
		case SHADER_PARAM::FLOAT_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::FLOAT_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrFloat[iIdx]);
			//inputShaderParameterValueStr.Format(L"%f", ((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrFloat[iIdx]);
			break;
		case SHADER_PARAM::VEC2_0:
		case SHADER_PARAM::VEC2_1:
		case SHADER_PARAM::VEC2_2:
		case SHADER_PARAM::VEC2_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::VEC2_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec2[iIdx].x);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec2[iIdx].y);
			//m_param.arrVec2[iIdx] = *((Vec2*)_pSrc);
			break;
		case SHADER_PARAM::VEC4_0:
		case SHADER_PARAM::VEC4_1:
		case SHADER_PARAM::VEC4_2:
		case SHADER_PARAM::VEC4_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::VEC4_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].x);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].y);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].z);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].w);
			//m_param.arrVec4[iIdx] = *((Vec4*)_pSrc);
			break;
		case SHADER_PARAM::MAT_0:
		case SHADER_PARAM::MAT_1:
		case SHADER_PARAM::MAT_2:
		case SHADER_PARAM::MAT_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::MAT_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._11);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._12);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._13);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._14);

			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._21);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._22);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._23);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._24);

			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._31);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._32);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._33);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._34);

			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._41);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._42);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._43);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._44);

			//m_param.arrMat[iIdx] = *((Matrix*)_pSrc);
			break;
		}



		for (int index = 0; index < inputShaderParameterValue.size(); index++)
		{
			CString inputShaderParameterValueStr;

			listctrlShaderParameterValue.SetItemText(index, 1, inputShaderParameterValueStr);
		}
	}
	else
	{
		int iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::INT_0;
		CString inputShaderParameterValueStr;
		inputShaderParameterValueStr.Format(L"%d", ((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrInt[iIdx]);
		listctrlShaderParameterValue.SetItemText(0, 1, inputShaderParameterValueStr);
	}
	
	
}
