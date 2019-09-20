// Animator2DDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Animator2DDlg.h"
#include "afxdialogex.h"

#include "AddAnimDlg.h"

#include <GameObject.h>
#include <Animator2D.h>
#include <Animation2D.h>


// CAnimator2DDlg 대화 상자

IMPLEMENT_DYNAMIC(CAnimator2DDlg, CDialogEx)


CAnimator2DDlg::CAnimator2DDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_ANIMATOR2DDLG, pParent)
	, m_bRepeat(FALSE)	
{
}

CAnimator2DDlg::~CAnimator2DDlg()
{	
}

void CAnimator2DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbAnimList);
	DDX_Control(pDX, IDC_BUTTON2, m_btnPlay);
	DDX_Check(pDX, IDC_CHECK2, m_bRepeat);
}


void CAnimator2DDlg::init(CGameObject * _pTarget)
{
	// GameObject 의 Animator2D 컴포넌트로 부터 Animation 목록을 읽어온다.
	SetTarget(_pTarget);
	
	if (nullptr == _pTarget->Animator2D())
		return;

	CAnimator2D* pAnimator = GetTarget()->Animator2D();

	const map<wstring, CAnimation2D*>& mapAnim = pAnimator->GetAnimList();

	for (const auto& pair : mapAnim)
	{
		m_cbAnimList.AddString(pair.first.c_str());
	}
}

// 상시 상태값 체크
void CAnimator2DDlg::Animator2DStateCheck(CGameObject* _pTarget)
{
	SetTarget(_pTarget);

	CAnimation2D* pCurAnim = _pTarget->Animator2D()->GetCurAnim();
	if (nullptr == pCurAnim)
		return;

	// 반복재생 아님, Animation 이 종료됨 
	if (pCurAnim->IsFinish() && !_pTarget->Animator2D()->IsRepeat())
	{
		m_btnPlay.SetWindowTextW(L"▶");
	}
}

void CAnimator2DDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	if (IsCbActive())
		return;
	   	 
	CAnimator2D* pAnimator = GetTarget()->Animator2D();

	// 목록 갱신
	m_cbAnimList.ResetContent();

	const map<wstring, CAnimation2D*>& mapAnim = pAnimator->GetAnimList();
	for (const auto& pair : mapAnim)
	{
		m_cbAnimList.AddString(pair.first.c_str());
	}	

	// 현재 재생중인 애니메이션을 목록에서 선택
	CAnimation2D* pCurAnim = pAnimator->GetCurAnim();

	if (nullptr != pCurAnim)
	{
		CString strCurName = pCurAnim->GetName().c_str();
		int idx = m_cbAnimList.FindString(0, strCurName);
		
		//if(-1 == idx)

		m_cbAnimList.SetCurSel(idx);
	}
}


BEGIN_MESSAGE_MAP(CAnimator2DDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnimator2DDlg::OnBtnPlay)
	ON_BN_CLICKED(IDC_CHECK2, &CAnimator2DDlg::OnBtnRepeat)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAnimator2DDlg::OnCbAnimChange)

	ON_CONTROL_RANGE(CBN_SETFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbSetfocusEdit)
	ON_CONTROL_RANGE(CBN_KILLFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbKillfocusEdit)

	ON_BN_CLICKED(IDC_BUTTON1, &CAnimator2DDlg::OnAddAnimation)
END_MESSAGE_MAP()


// CAnimator2DDlg 메시지 처리기


void CAnimator2DDlg::OnBtnPlay()
{	
	CAnimation2D* pAnim = GetTarget()->Animator2D()->GetCurAnim();

	OnOK();

	if (nullptr == pAnim)
		return;

	if (pAnim->IsPlay())
	{
		pAnim->Pause();
		m_btnPlay.SetWindowTextW(L"▶");
	}
	else
	{
		GetTarget()->Animator2D()->SetRepeat(m_bRepeat);
		pAnim->Play();
		m_btnPlay.SetWindowTextW(L"∥");
	}	
}

void CAnimator2DDlg::OnBtnRepeat()
{
	UpdateData();

	CAnimation2D* pAnim = GetTarget()->Animator2D()->GetCurAnim();
	if (pAnim->IsPlay())
	{
		GetTarget()->Animator2D()->SetRepeat(m_bRepeat);
	}
}


void CAnimator2DDlg::OnCbAnimChange()
{
	int iIdx = m_cbAnimList.GetCurSel();
	CString str;
	m_cbAnimList.GetLBText(iIdx, str);
	GetTarget()->Animator2D()->PlayAnimation(str.GetBuffer(), m_bRepeat);
	GetTarget()->Animator2D()->Pause();

	m_btnPlay.SetWindowTextW(L"▶");
}


void CAnimator2DDlg::OnAddAnimation()
{
	CAddAnimDlg dlg;

	dlg.SetTargetObject(GetTarget());


	dlg.DoModal();


	

}
