﻿// DbgView.cpp: 구현 파일
//

#include "stdafx.h"
#include "DbgView.h"

#include "resource.h"

// CDbgView

IMPLEMENT_DYNCREATE(CDbgView, CView)

CDbgView::CDbgView()
	: CFormView(IDD_DBGVIEW)
{

}

CDbgView::~CDbgView()
{
}

BEGIN_MESSAGE_MAP(CDbgView, CView)
END_MESSAGE_MAP()


// CDbgView 그리기

void CDbgView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CDbgView 진단

#ifdef _DEBUG
void CDbgView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDbgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDbgView 메시지 처리기
