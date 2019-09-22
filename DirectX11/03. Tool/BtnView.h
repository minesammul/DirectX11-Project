﻿#pragma once


// CBtnView 보기

class CBtnView : public CFormView
{
	DECLARE_DYNCREATE(CBtnView)

protected:
	CBtnView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CBtnView();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BTNVIEW };
#endif

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void DoDataExchange(CDataExchange* pDX);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnPlay();
		
	CButton m_btnPlay;
	CButton m_btnPause;
	CButton m_btnNextFrm;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnPause();
	afx_msg void OnBtnNextStep();
	CButton collisionLayerButton;
	afx_msg void OnBnClickedButtonCollisionLayer();
};


