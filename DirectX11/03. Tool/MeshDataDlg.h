#pragma once
#include "ResInfoDlg.h"

// CMeshDataDlg 대화 상자

class CMeshDataDlg : public CResInfoDlg
{
	DECLARE_DYNAMIC(CMeshDataDlg)

public:
	CMeshDataDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMeshDataDlg();

public:
	void SetResource(CResource* _pRes);
	BOOL OnInitDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESHDATADLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit animationStartFrame;
	CEdit animationEndFrame;
	CListCtrl nowAnimationListCtrl;
	afx_msg void OnBnClickedButtonNewAniInsert();
	CEdit newAniName;
	afx_msg void OnBnClickedButtonCreateFBXObject();
	CEdit editCreateFBXObjectName;
};
