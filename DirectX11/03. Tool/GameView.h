﻿#pragma once
#include <Engine/Material.h>
#include <Engine/Shader.h>

// CGameView 보기
class CGameObject;
class CGameView : public CView
{
	DECLARE_DYNCREATE(CGameView)
private:
	CGameObject*			m_pToolCam;
	CGameObject*			m_pToolUICam;
	CGameObject*			m_pGridObject;


	vector<CGameObject*>	m_vecToolUI;
	CMaterial*				m_pGridMtrl;
	CShader*				m_pGridShader;

public:
	void init();
	void update();

	void DeleteResource();

private:
	void update_tool();
	void render_tool();

private:
	void CreateToolResource();
	void CreateToolCamera();
	void CreateToolObject();

public:
	CGameObject* GetToolCamera() { return m_pToolCam; }

protected:
	CGameView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CGameView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


