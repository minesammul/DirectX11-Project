#pragma once

#include "ComponentDlg.h"

class CGameObject;
class CLight3D;

class CLight3DDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CLight3DDlg)
private:
	CLight3D* m_light3D;
	bool m_focus;


public:
	virtual void init(CGameObject* _pTarget);

	void update(CGameObject* _pTarget);

public:
	CLight3DDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLight3DDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIGHT3DDLG };
#endif


private:
	void UpdateLightType();
	void UpdateLightDirection();
	void UpdateLightDiffuse();
	void UpdateLightSpecular();
	void UpdateLightAmbient();
	void UpdateLightRange();
	void UpdateLightAngle();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboboxLightType;
	afx_msg void OnCbnSelchangeComboLightType();
	CEdit m_editDirectionX;
	CEdit m_editDirectionY;
	CEdit m_editDirectionZ;
	afx_msg void OnEnKillfocusEditDirectionX();
	afx_msg void OnEnSetfocusEditDirectionX();
	afx_msg void OnEnKillfocusEditDirectionY();
	afx_msg void OnEnSetfocusEditDirectionY();
	afx_msg void OnEnKillfocusEditDirectionZ();
	afx_msg void OnEnSetfocusEditDirectionZ();
	CSliderCtrl m_sliderDiffuse;
	afx_msg void OnNMReleasedcaptureSliderDiffuse(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_slideSpecular;
	afx_msg void OnNMReleasedcaptureSliderSpecular(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slideAmbient;
	afx_msg void OnNMReleasedcaptureSliderAmbient(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editRange;
	CEdit m_editAngle;
	afx_msg void OnEnKillfocusEditRange();
	afx_msg void OnEnSetfocusEditRange();
	afx_msg void OnEnKillfocusEditAngle();
	afx_msg void OnEnSetfocusEditAngle();
};
