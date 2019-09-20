#pragma once


#include "ComponentDlg.h"

class CAnimator2DDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CAnimator2DDlg)

public:

	virtual void init(CGameObject* _pTarget);
	virtual void update(CGameObject* _pTarget);

	void Animator2DStateCheck(CGameObject* _pTarget);




public:
	CAnimator2DDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnimator2DDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATOR2DDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox	m_cbAnimList;
	CButton		m_btnPlay;
	BOOL		m_bRepeat;

	afx_msg void OnBtnPlay();
	afx_msg void OnBtnRepeat();
	afx_msg void OnCbAnimChange();
	afx_msg void OnAddAnimation();
};
