// Collider3DDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Collider3DDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <Collider3D.h>

// CCollider3DDlg 대화 상자

IMPLEMENT_DYNAMIC(CCollider3DDlg, CDialogEx)

CCollider3DDlg::CCollider3DDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_COLLIDER3DDLG, pParent)
{
	focus = false;
}

CCollider3DDlg::~CCollider3DDlg()
{
}

void CCollider3DDlg::UpdatePosition(CGameObject * target)
{
	CCollider3D* targetCollider3D = target->Collider3D();
	Vec3 collider3DPosition = targetCollider3D->GetOffset();

	CString inputStr;
	inputStr.Format(L"%f", collider3DPosition.x);
	editPositionX.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider3DPosition.y);
	editPositionY.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider3DPosition.z);
	editPositionZ.SetWindowTextW(inputStr);
}

void CCollider3DDlg::UpdateScale(CGameObject * target)
{
	CCollider3D* targetCollider3D = target->Collider3D();
	Vec3 collider3DScale = targetCollider3D->GetScale();

	CString inputStr;
	inputStr.Format(L"%f", collider3DScale.x);
	editScaleX.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider3DScale.y);
	editScaleY.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider3DScale.z);
	editScaleZ.SetWindowTextW(inputStr);
}

void CCollider3DDlg::UpdateRotation(CGameObject * target)
{
}

void CCollider3DDlg::init(CGameObject * _pTarget)
{
}

void CCollider3DDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);
	if (_pTarget == nullptr)
	{
		return;
	}

	if (focus == true)
	{
		return;
	}

	UpdatePosition(_pTarget);
	UpdateScale(_pTarget);
}

void CCollider3DDlg::OnOK()
{
	focus = false;
	CComponentDlg::OnOK();
}

void CCollider3DDlg::OnCancel()
{
}

void CCollider3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editPositionX);
	DDX_Control(pDX, IDC_EDIT2, editPositionY);
	DDX_Control(pDX, IDC_EDIT3, editPositionZ);
	DDX_Control(pDX, IDC_EDIT4, editScaleX);
	DDX_Control(pDX, IDC_EDIT5, editScaleY);
	DDX_Control(pDX, IDC_EDIT6, editScaleZ);
	DDX_Control(pDX, IDC_EDIT7, editRotationX);
	DDX_Control(pDX, IDC_EDIT8, editRotationY);
	DDX_Control(pDX, IDC_EDIT9, editRotationZ);
}


BEGIN_MESSAGE_MAP(CCollider3DDlg, CDialogEx)
	ON_EN_SETFOCUS(IDC_EDIT1, &CCollider3DDlg::OnEnSetfocusEditPositionX)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CCollider3DDlg::OnEnKillfocusEditPositionX)
	ON_EN_SETFOCUS(IDC_EDIT2, &CCollider3DDlg::OnEnSetfocusEditPositionY)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CCollider3DDlg::OnEnKillfocusEditPositionY)
	ON_EN_SETFOCUS(IDC_EDIT3, &CCollider3DDlg::OnEnSetfocusEditPositionZ)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CCollider3DDlg::OnEnKillfocusEditPositionZ)
	ON_EN_SETFOCUS(IDC_EDIT4, &CCollider3DDlg::OnEnSetfocusEditScaleX)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CCollider3DDlg::OnEnKillfocusEditScaleX)
	ON_EN_SETFOCUS(IDC_EDIT5, &CCollider3DDlg::OnEnSetfocusEditScaleY)
	ON_EN_KILLFOCUS(IDC_EDIT5, &CCollider3DDlg::OnEnKillfocusEditScaleY)
	ON_EN_SETFOCUS(IDC_EDIT6, &CCollider3DDlg::OnEnSetfocusEditScaleZ)
	ON_EN_KILLFOCUS(IDC_EDIT6, &CCollider3DDlg::OnEnKillfocusEditScaleZ)
END_MESSAGE_MAP()


// CCollider3DDlg 메시지 처리기


void CCollider3DDlg::OnEnSetfocusEditPositionX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void CCollider3DDlg::OnEnKillfocusEditPositionX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider3D()->GetOffset();
		CString inputStr;
		editPositionX.GetWindowTextW(inputStr);
		inputVec3.x = static_cast<float>(_wtof(inputStr));
		target->Collider3D()->SetOffset(inputVec3);
	}
}


void CCollider3DDlg::OnEnSetfocusEditPositionY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void CCollider3DDlg::OnEnKillfocusEditPositionY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider3D()->GetOffset();
		CString inputStr;
		editPositionY.GetWindowTextW(inputStr);
		inputVec3.y = static_cast<float>(_wtof(inputStr));
		target->Collider3D()->SetOffset(inputVec3);
	}
}


void CCollider3DDlg::OnEnSetfocusEditPositionZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void CCollider3DDlg::OnEnKillfocusEditPositionZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider3D()->GetOffset();
		CString inputStr;
		editPositionZ.GetWindowTextW(inputStr);
		inputVec3.z = static_cast<float>(_wtof(inputStr));
		target->Collider3D()->SetOffset(inputVec3);
	}
}


void CCollider3DDlg::OnEnSetfocusEditScaleX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void CCollider3DDlg::OnEnKillfocusEditScaleX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider3D()->GetScale();
		CString inputStr;
		editScaleX.GetWindowTextW(inputStr);
		inputVec3.x = static_cast<float>(_wtof(inputStr));
		target->Collider3D()->SetScale(inputVec3);
	}
}


void CCollider3DDlg::OnEnSetfocusEditScaleY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void CCollider3DDlg::OnEnKillfocusEditScaleY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider3D()->GetScale();
		CString inputStr;
		editScaleY.GetWindowTextW(inputStr);
		inputVec3.y = static_cast<float>(_wtof(inputStr));
		target->Collider3D()->SetScale(inputVec3);
	}
}


void CCollider3DDlg::OnEnSetfocusEditScaleZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void CCollider3DDlg::OnEnKillfocusEditScaleZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider3D()->GetScale();
		CString inputStr;
		editScaleZ.GetWindowTextW(inputStr);
		inputVec3.z = static_cast<float>(_wtof(inputStr));
		target->Collider3D()->SetScale(inputVec3);
	}
}
