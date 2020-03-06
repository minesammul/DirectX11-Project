#pragma once
#include "ComponentDlg.h"

// CParticleDlg 대화 상자
class CGameObject;
class CParticleDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CParticleDlg)
public:
	virtual void init(CGameObject* _pTarget);
	void update(CGameObject* _pTarget);

public:
	CParticleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CParticleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARTICLEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	bool isFocus;

public:
	CEdit startColorR;
	CEdit startColorG;
	CEdit startColorB;
	CEdit startColorA;
	CEdit endColorR;
	CEdit endColorG;
	CEdit endColorB;
	CEdit endColorA;
	CEdit startScale;
	CEdit endScale;
	CEdit minSpeed;
	CEdit maxSpeed;
	CEdit minLifeTime;
	CEdit maxLifeTime;
	CEdit frequencyTime;
	CEdit maxParticleCount;
	CEdit usingTexture;
	afx_msg void OnEnChangeStartColorR();
	afx_msg void OnEnSetfocusStartColorR();
	afx_msg void OnEnKillfocusEditStartColorR();
	afx_msg void OnEnChangeStartColorG();
	afx_msg void OnEnSetfocusStartColorG();
	afx_msg void OnEnKillfocusStartColorG();
	afx_msg void OnEnChangeStartColorB();
	afx_msg void OnEnSetfocusStartColorB();
	afx_msg void OnEnKillfocusStartColorB();
	afx_msg void OnEnChangeStartColorA();
	afx_msg void OnEnSetfocusStartColorA();
	afx_msg void OnEnKillfocusStartColorA();
	afx_msg void OnEnChangeEndColorR();
	afx_msg void OnEnSetfocusEndColorR();
	afx_msg void OnEnKillfocusEndColorR();
	afx_msg void OnEnChangeEndColorG();
	afx_msg void OnEnSetfocusEndColorG();
	afx_msg void OnEnKillfocusEndColorG();
	afx_msg void OnEnChangeEndColorB();
	afx_msg void OnEnSetfocusEndColorB();
	afx_msg void OnEnKillfocusEndColorB();
	afx_msg void OnEnChangeEndColorA();
	afx_msg void OnEnSetfocusEndColorA();
	afx_msg void OnEnKillfocusEndColorA();
	afx_msg void OnEnChangeStartScale();
	afx_msg void OnEnSetfocusStartScale();
	afx_msg void OnEnKillfocusStartScale();
	afx_msg void OnEnChangeEndScale();
	afx_msg void OnEnSetfocusEndScale();
	afx_msg void OnEnKillfocusEndScale();
	afx_msg void OnEnChangeStartSpeed();
	afx_msg void OnEnSetfocusStartSpeed();
	afx_msg void OnEnKillfocusStartSpeed();
	afx_msg void OnEnChangeEndSpeed();
	afx_msg void OnEnSetfocusEndSpeed();
	afx_msg void OnEnKillfocusEndSpeed();
	afx_msg void OnEnChangeMinLifeTime();
	afx_msg void OnEnSetfocusMinLifeTime();
	afx_msg void OnEnKillfocusMinLifeTime();
	afx_msg void OnEnChangeMaxLifeTime();
	afx_msg void OnEnSetfocusMaxLifeTime();
	afx_msg void OnEnKillfocusMaxLifeTime();
	afx_msg void OnEnChangeFrequencyTime();
	afx_msg void OnEnSetfocusFrequencyTime();
	afx_msg void OnEnKillfocusFrequencyTime();
	afx_msg void OnEnChangeMaxCount();
	afx_msg void OnEnSetfocusMaxCount();
	afx_msg void OnEnKillfocusMaxCount();
	afx_msg void OnBnClickedTexture();
};
