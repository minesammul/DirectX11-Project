// Light3DDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Light3DDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <Light3D.h>

// CLight3DDlg 대화 상자

IMPLEMENT_DYNAMIC(CLight3DDlg, CDialogEx)

void CLight3DDlg::init(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	CGameObject* target = _pTarget;
	if (target != nullptr)
	{
		m_focus = false;

		m_comboboxLightType.ResetContent();

		m_light3D = GetTarget()->Light3D();

		m_comboboxLightType.InsertString(0, L"Direction");
		m_comboboxLightType.InsertString(1, L"Point");
		m_comboboxLightType.InsertString(2, L"Spot");
	}
}

void CLight3DDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	if (m_focus == true)
	{
		return;
	}

	UpdateLightType();
	UpdateLightDirection();
	UpdateLightDiffuse();
	UpdateLightSpecular();
	UpdateLightAmbient();
	UpdateLightRange();
	UpdateLightAngle();
}

CLight3DDlg::CLight3DDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_LIGHT3DDLG, pParent)
{

}

CLight3DDlg::~CLight3DDlg()
{
}

void CLight3DDlg::UpdateLightType()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	int iType = lightData.iType;
	m_comboboxLightType.SetCurSel(iType);
}

void CLight3DDlg::UpdateLightDirection()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	Vector4 vLightDirection = lightData.vDir;
	
	CString strDirectionValue;

	strDirectionValue.Format(L"%f", vLightDirection.x);
	m_editDirectionX.SetWindowTextW(strDirectionValue);

	strDirectionValue.Format(L"%f", vLightDirection.y);
	m_editDirectionY.SetWindowTextW(strDirectionValue);

	strDirectionValue.Format(L"%f", vLightDirection.z);
	m_editDirectionZ.SetWindowTextW(strDirectionValue);
}

void CLight3DDlg::UpdateLightDiffuse()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	Vector4 vLightDiffuse = lightData.vDiff;

	int iSlidePos = vLightDiffuse.x * 100;

	m_sliderDiffuse.SetPos(iSlidePos);
}

void CLight3DDlg::UpdateLightSpecular()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	Vector4 vLightSpecular = lightData.vSpec;

	int iSlidePos = vLightSpecular.x * 100;

	m_slideSpecular.SetPos(iSlidePos);
}

void CLight3DDlg::UpdateLightAmbient()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	Vector4 vLightAmbient = lightData.vAmb;

	int iSlidePos = vLightAmbient.x * 100;

	m_slideAmbient.SetPos(iSlidePos);
}

void CLight3DDlg::UpdateLightRange()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	float fLightRange = lightData.fRange;

	CString strValue;

	strValue.Format(L"%f", fLightRange);
	m_editRange.SetWindowTextW(strValue);
}

void CLight3DDlg::UpdateLightAngle()
{
	tLight3DInfo lightData = m_light3D->GetLight3DInfo();
	float fLightAngle = lightData.fAngle;

	fLightAngle = XMConvertToDegrees(fLightAngle);

	CString strValue;

	strValue.Format(L"%f", fLightAngle);
	m_editAngle.SetWindowTextW(strValue);
}

void CLight3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboboxLightType);
	DDX_Control(pDX, IDC_EDIT1, m_editDirectionX);
	DDX_Control(pDX, IDC_EDIT2, m_editDirectionY);
	DDX_Control(pDX, IDC_EDIT3, m_editDirectionZ);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderDiffuse);
	DDX_Control(pDX, IDC_SLIDER2, m_slideSpecular);
	DDX_Control(pDX, IDC_SLIDER3, m_slideAmbient);
	DDX_Control(pDX, IDC_EDIT4, m_editRange);
	DDX_Control(pDX, IDC_EDIT5, m_editAngle);
}


BEGIN_MESSAGE_MAP(CLight3DDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CLight3DDlg::OnCbnSelchangeComboLightType)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CLight3DDlg::OnEnKillfocusEditDirectionX)
	ON_EN_SETFOCUS(IDC_EDIT1, &CLight3DDlg::OnEnSetfocusEditDirectionX)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CLight3DDlg::OnEnKillfocusEditDirectionY)
	ON_EN_SETFOCUS(IDC_EDIT2, &CLight3DDlg::OnEnSetfocusEditDirectionY)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CLight3DDlg::OnEnKillfocusEditDirectionZ)
	ON_EN_SETFOCUS(IDC_EDIT3, &CLight3DDlg::OnEnSetfocusEditDirectionZ)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CLight3DDlg::OnNMReleasedcaptureSliderDiffuse)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &CLight3DDlg::OnNMReleasedcaptureSliderSpecular)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER3, &CLight3DDlg::OnNMReleasedcaptureSliderAmbient)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CLight3DDlg::OnEnKillfocusEditRange)
	ON_EN_SETFOCUS(IDC_EDIT4, &CLight3DDlg::OnEnSetfocusEditRange)
	ON_EN_KILLFOCUS(IDC_EDIT5, &CLight3DDlg::OnEnKillfocusEditAngle)
	ON_EN_SETFOCUS(IDC_EDIT5, &CLight3DDlg::OnEnSetfocusEditAngle)
END_MESSAGE_MAP()


// CLight3DDlg 메시지 처리기


void CLight3DDlg::OnCbnSelchangeComboLightType()
{
	int iSelectIndex = m_comboboxLightType.GetCurSel();
	m_light3D->SetLightType((LIGHT_TYPE)iSelectIndex);
}


void CLight3DDlg::OnEnKillfocusEditDirectionX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = false;

	CString strDirectionValue;
	m_editDirectionX.GetWindowTextW(strDirectionValue);

	float fLightDirectionX = _wtof(strDirectionValue);

	tLight3DInfo tLightData = m_light3D->GetLight3DInfo();
	Vector4 vLightDirection = tLightData.vDir;
	vLightDirection.x = fLightDirectionX;

	Vector3 vResultDirection = Vector3(vLightDirection.x, vLightDirection.y, vLightDirection.z);

	m_light3D->SetLightDir(vResultDirection);
}


void CLight3DDlg::OnEnSetfocusEditDirectionX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = true;
}


void CLight3DDlg::OnEnKillfocusEditDirectionY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = false;

	CString strDirectionValue;
	m_editDirectionY.GetWindowTextW(strDirectionValue);

	float fLightDirectionY = _wtof(strDirectionValue);

	tLight3DInfo tLightData = m_light3D->GetLight3DInfo();
	Vector4 vLightDirection = tLightData.vDir;
	vLightDirection.y = fLightDirectionY;

	Vector3 vResultDirection = Vector3(vLightDirection.x, vLightDirection.y, vLightDirection.z);

	m_light3D->SetLightDir(vResultDirection);
}


void CLight3DDlg::OnEnSetfocusEditDirectionY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = true;
}


void CLight3DDlg::OnEnKillfocusEditDirectionZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = false;

	CString strDirectionValue;
	m_editDirectionZ.GetWindowTextW(strDirectionValue);

	float fLightDirectionZ = _wtof(strDirectionValue);

	tLight3DInfo tLightData = m_light3D->GetLight3DInfo();
	Vector4 vLightDirection = tLightData.vDir;
	vLightDirection.z = fLightDirectionZ;

	Vector3 vResultDirection = Vector3(vLightDirection.x, vLightDirection.y, vLightDirection.z);

	m_light3D->SetLightDir(vResultDirection);
}


void CLight3DDlg::OnEnSetfocusEditDirectionZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = true;
}


void CLight3DDlg::OnNMReleasedcaptureSliderDiffuse(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_focus = false;

	int iSlidePos = m_sliderDiffuse.GetPos();
	float fChangeDiffusePower = iSlidePos / 100.f;
	
	Vector3 vDiffusePower = Vector3(fChangeDiffusePower, 
									fChangeDiffusePower, 
									fChangeDiffusePower);

	m_light3D->SetLightDiffuse(vDiffusePower);

	*pResult = 0;
}


void CLight3DDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_focus = true;

	CComponentDlg::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CLight3DDlg::OnNMReleasedcaptureSliderSpecular(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_focus = false;

	int iSlidePos = m_slideSpecular.GetPos();
	float fChangeSpecularPower = iSlidePos / 100.f;

	Vector3 vSpecularPower = Vector3(	fChangeSpecularPower,
										fChangeSpecularPower,
										fChangeSpecularPower);

	m_light3D->SetLightSpecular(vSpecularPower);

	*pResult = 0;
}


void CLight3DDlg::OnNMReleasedcaptureSliderAmbient(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = false;

	int iSlidePos = m_slideAmbient.GetPos();
	float fChangeAmbientPower = iSlidePos / 100.f;

	Vector3 vAmbientPower = Vector3(fChangeAmbientPower,
									fChangeAmbientPower,
									fChangeAmbientPower);

	m_light3D->SetLightAmbient(vAmbientPower);

	*pResult = 0;
}


void CLight3DDlg::OnEnKillfocusEditRange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	m_editRange.GetWindowTextW(strValue);

	float fLightRange = _wtof(strValue);

	m_light3D->SetLightRange(fLightRange);
}


void CLight3DDlg::OnEnSetfocusEditRange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = true;
}


void CLight3DDlg::OnEnKillfocusEditAngle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	m_editAngle.GetWindowTextW(strValue);

	float fLightAngle = _wtof(strValue);

	m_light3D->SetLightAngle(fLightAngle);
}


void CLight3DDlg::OnEnSetfocusEditAngle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_focus = true;
}
