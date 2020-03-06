// ParticleDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ParticleDlg.h"
#include "afxdialogex.h"

#include "ListDlg.h"

#include <GameObject.h>
#include <Transform.h>
#include <EventMgr.h>
#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>
#include <func.h>
#include <ParticleSystem.h>
#include <ResMgr.h>

// CParticleDlg 대화 상자

IMPLEMENT_DYNAMIC(CParticleDlg, CDialogEx)


CParticleDlg::CParticleDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_PARTICLEDLG, pParent)
{

}

CParticleDlg::~CParticleDlg()
{
}

void CParticleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, startColorR);
	DDX_Control(pDX, IDC_EDIT2, startColorG);
	DDX_Control(pDX, IDC_EDIT3, startColorB);
	DDX_Control(pDX, IDC_EDIT4, startColorA);
	DDX_Control(pDX, IDC_EDIT5, endColorR);
	DDX_Control(pDX, IDC_EDIT6, endColorG);
	DDX_Control(pDX, IDC_EDIT7, endColorB);
	DDX_Control(pDX, IDC_EDIT8, endColorA);
	DDX_Control(pDX, IDC_EDIT9, startScale);
	DDX_Control(pDX, IDC_EDIT10, endScale);
	DDX_Control(pDX, IDC_EDIT11, minSpeed);
	DDX_Control(pDX, IDC_EDIT12, maxSpeed);
	DDX_Control(pDX, IDC_EDIT13, minLifeTime);
	DDX_Control(pDX, IDC_EDIT14, maxLifeTime);
	DDX_Control(pDX, IDC_EDIT15, frequencyTime);
	DDX_Control(pDX, IDC_EDIT16, maxParticleCount);
	DDX_Control(pDX, IDC_EDIT17, usingTexture);
}


BEGIN_MESSAGE_MAP(CParticleDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CParticleDlg::OnEnChangeStartColorR)
	ON_EN_SETFOCUS(IDC_EDIT1, &CParticleDlg::OnEnSetfocusStartColorR)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CParticleDlg::OnEnKillfocusEditStartColorR)
	ON_EN_CHANGE(IDC_EDIT2, &CParticleDlg::OnEnChangeStartColorG)
	ON_EN_SETFOCUS(IDC_EDIT2, &CParticleDlg::OnEnSetfocusStartColorG)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CParticleDlg::OnEnKillfocusStartColorG)
	ON_EN_CHANGE(IDC_EDIT3, &CParticleDlg::OnEnChangeStartColorB)
	ON_EN_SETFOCUS(IDC_EDIT3, &CParticleDlg::OnEnSetfocusStartColorB)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CParticleDlg::OnEnKillfocusStartColorB)
	ON_EN_CHANGE(IDC_EDIT4, &CParticleDlg::OnEnChangeStartColorA)
	ON_EN_SETFOCUS(IDC_EDIT4, &CParticleDlg::OnEnSetfocusStartColorA)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CParticleDlg::OnEnKillfocusStartColorA)
	ON_EN_CHANGE(IDC_EDIT5, &CParticleDlg::OnEnChangeEndColorR)
	ON_EN_SETFOCUS(IDC_EDIT5, &CParticleDlg::OnEnSetfocusEndColorR)
	ON_EN_KILLFOCUS(IDC_EDIT5, &CParticleDlg::OnEnKillfocusEndColorR)
	ON_EN_CHANGE(IDC_EDIT6, &CParticleDlg::OnEnChangeEndColorG)
	ON_EN_SETFOCUS(IDC_EDIT6, &CParticleDlg::OnEnSetfocusEndColorG)
	ON_EN_KILLFOCUS(IDC_EDIT6, &CParticleDlg::OnEnKillfocusEndColorG)
	ON_EN_CHANGE(IDC_EDIT7, &CParticleDlg::OnEnChangeEndColorB)
	ON_EN_SETFOCUS(IDC_EDIT7, &CParticleDlg::OnEnSetfocusEndColorB)
	ON_EN_KILLFOCUS(IDC_EDIT7, &CParticleDlg::OnEnKillfocusEndColorB)
	ON_EN_CHANGE(IDC_EDIT8, &CParticleDlg::OnEnChangeEndColorA)
	ON_EN_SETFOCUS(IDC_EDIT8, &CParticleDlg::OnEnSetfocusEndColorA)
	ON_EN_KILLFOCUS(IDC_EDIT8, &CParticleDlg::OnEnKillfocusEndColorA)
	ON_EN_CHANGE(IDC_EDIT9, &CParticleDlg::OnEnChangeStartScale)
	ON_EN_SETFOCUS(IDC_EDIT9, &CParticleDlg::OnEnSetfocusStartScale)
	ON_EN_KILLFOCUS(IDC_EDIT9, &CParticleDlg::OnEnKillfocusStartScale)
	ON_EN_CHANGE(IDC_EDIT10, &CParticleDlg::OnEnChangeEndScale)
	ON_EN_SETFOCUS(IDC_EDIT10, &CParticleDlg::OnEnSetfocusEndScale)
	ON_EN_KILLFOCUS(IDC_EDIT10, &CParticleDlg::OnEnKillfocusEndScale)
	ON_EN_CHANGE(IDC_EDIT11, &CParticleDlg::OnEnChangeStartSpeed)
	ON_EN_SETFOCUS(IDC_EDIT11, &CParticleDlg::OnEnSetfocusStartSpeed)
	ON_EN_KILLFOCUS(IDC_EDIT11, &CParticleDlg::OnEnKillfocusStartSpeed)
	ON_EN_CHANGE(IDC_EDIT12, &CParticleDlg::OnEnChangeEndSpeed)
	ON_EN_SETFOCUS(IDC_EDIT12, &CParticleDlg::OnEnSetfocusEndSpeed)
	ON_EN_KILLFOCUS(IDC_EDIT12, &CParticleDlg::OnEnKillfocusEndSpeed)
	ON_EN_CHANGE(IDC_EDIT13, &CParticleDlg::OnEnChangeMinLifeTime)
	ON_EN_SETFOCUS(IDC_EDIT13, &CParticleDlg::OnEnSetfocusMinLifeTime)
	ON_EN_KILLFOCUS(IDC_EDIT13, &CParticleDlg::OnEnKillfocusMinLifeTime)
	ON_EN_CHANGE(IDC_EDIT14, &CParticleDlg::OnEnChangeMaxLifeTime)
	ON_EN_SETFOCUS(IDC_EDIT14, &CParticleDlg::OnEnSetfocusMaxLifeTime)
	ON_EN_KILLFOCUS(IDC_EDIT14, &CParticleDlg::OnEnKillfocusMaxLifeTime)
	ON_EN_CHANGE(IDC_EDIT15, &CParticleDlg::OnEnChangeFrequencyTime)
	ON_EN_SETFOCUS(IDC_EDIT15, &CParticleDlg::OnEnSetfocusFrequencyTime)
	ON_EN_KILLFOCUS(IDC_EDIT15, &CParticleDlg::OnEnKillfocusFrequencyTime)
	ON_EN_CHANGE(IDC_EDIT16, &CParticleDlg::OnEnChangeMaxCount)
	ON_EN_SETFOCUS(IDC_EDIT16, &CParticleDlg::OnEnSetfocusMaxCount)
	ON_EN_KILLFOCUS(IDC_EDIT16, &CParticleDlg::OnEnKillfocusMaxCount)
	ON_BN_CLICKED(IDC_BUTTON1, &CParticleDlg::OnBnClickedTexture)
END_MESSAGE_MAP()


// CParticleDlg 메시지 처리기

void CParticleDlg::init(CGameObject * _pTarget)
{
	isFocus = false;
}

void CParticleDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	if (isFocus == true)
	{
		return;
	}


	{
		Vec4 startColor = GetTarget()->Particle()->GetStartColor();

		CString inputStr;

		inputStr.Format(L"%f", startColor.x);
		startColorR.SetWindowTextW(inputStr);

		inputStr.Format(L"%f", startColor.y);
		startColorG.SetWindowTextW(inputStr);

		inputStr.Format(L"%f", startColor.z);
		startColorB.SetWindowTextW(inputStr);

		inputStr.Format(L"%f", startColor.w);
		startColorA.SetWindowTextW(inputStr);
	}

	{
		Vec4 endColor = GetTarget()->Particle()->GetEndColor();

		CString inputStr;

		inputStr.Format(L"%f", endColor.x);
		endColorR.SetWindowTextW(inputStr);

		inputStr.Format(L"%f", endColor.y);
		endColorG.SetWindowTextW(inputStr);

		inputStr.Format(L"%f", endColor.z);
		endColorB.SetWindowTextW(inputStr);

		inputStr.Format(L"%f", endColor.w);
		endColorA.SetWindowTextW(inputStr);
	}

	{
		float particleStartScale = GetTarget()->Particle()->GetStartScale();

		CString inputStr;

		inputStr.Format(L"%f", particleStartScale);
		startScale.SetWindowTextW(inputStr);
	}

	{
		float particleEndScale = GetTarget()->Particle()->GetEndScale();

		CString inputStr;

		inputStr.Format(L"%f", particleEndScale);
		endScale.SetWindowTextW(inputStr);
	}

	{
		float particleMinSpeed = GetTarget()->Particle()->GetMinSpeed();

		CString inputStr;

		inputStr.Format(L"%f", particleMinSpeed);
		minSpeed.SetWindowTextW(inputStr);
	}

	{
		float particleMaxSpeed = GetTarget()->Particle()->GetMaxSpeed();

		CString inputStr;

		inputStr.Format(L"%f", particleMaxSpeed);
		maxSpeed.SetWindowTextW(inputStr);
	}

	{
		float particleMinLifeTime = GetTarget()->Particle()->GetMinLifeTime();

		CString inputStr;

		inputStr.Format(L"%f", particleMinLifeTime);
		minLifeTime.SetWindowTextW(inputStr);
	}

	{
		float particleMaxLifeTime = GetTarget()->Particle()->GetMaxLifeTime();

		CString inputStr;

		inputStr.Format(L"%f", particleMaxLifeTime);
		maxLifeTime.SetWindowTextW(inputStr);
	}


	{
		float particleFrequency = GetTarget()->Particle()->GetFrequency();

		CString inputStr;

		inputStr.Format(L"%f", particleFrequency);
		frequencyTime.SetWindowTextW(inputStr);
	}

	{
		int particleMaxCount = GetTarget()->Particle()->GetMaxParticleCount();

		CString inputStr;

		inputStr.Format(L"%d", particleMaxCount);
		maxParticleCount.SetWindowTextW(inputStr);
	}

	{
		wstring particleTextureName = GetTarget()->Particle()->GetParticleTextureName();

		CString inputStr = particleTextureName.c_str();
		usingTexture.SetWindowTextW(inputStr);
	}
}

void CParticleDlg::OnEnChangeStartColorR()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CString inputStr;
	startColorR.GetWindowTextW(inputStr);
	
	Vec4 particleStartColor = GetTarget()->Particle()->GetStartColor();
	particleStartColor.x = _wtof(inputStr);
	GetTarget()->Particle()->SetStartColor(particleStartColor);
}


void CParticleDlg::OnEnSetfocusStartColorR()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEditStartColorR()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeStartColorG()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	startColorG.GetWindowTextW(inputStr);

	Vec4 particleStartColor = GetTarget()->Particle()->GetStartColor();
	particleStartColor.y = _wtof(inputStr);
	GetTarget()->Particle()->SetStartColor(particleStartColor);
}


void CParticleDlg::OnEnSetfocusStartColorG()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusStartColorG()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeStartColorB()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	startColorB.GetWindowTextW(inputStr);

	Vec4 particleStartColor = GetTarget()->Particle()->GetStartColor();
	particleStartColor.z = _wtof(inputStr);
	GetTarget()->Particle()->SetStartColor(particleStartColor);
}


void CParticleDlg::OnEnSetfocusStartColorB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusStartColorB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeStartColorA()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	startColorA.GetWindowTextW(inputStr);

	Vec4 particleStartColor = GetTarget()->Particle()->GetStartColor();
	particleStartColor.w = _wtof(inputStr);
	GetTarget()->Particle()->SetStartColor(particleStartColor);
}


void CParticleDlg::OnEnSetfocusStartColorA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusStartColorA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeEndColorR()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	endColorR.GetWindowTextW(inputStr);

	Vec4 particleEndColor = GetTarget()->Particle()->GetEndColor();
	particleEndColor.x = _wtof(inputStr);
	GetTarget()->Particle()->SetEndColor(particleEndColor);

}


void CParticleDlg::OnEnSetfocusEndColorR()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEndColorR()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeEndColorG()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	endColorG.GetWindowTextW(inputStr);

	Vec4 particleEndColor = GetTarget()->Particle()->GetEndColor();
	particleEndColor.y = _wtof(inputStr);
	GetTarget()->Particle()->SetEndColor(particleEndColor);
}


void CParticleDlg::OnEnSetfocusEndColorG()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEndColorG()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeEndColorB()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	endColorB.GetWindowTextW(inputStr);

	Vec4 particleEndColor = GetTarget()->Particle()->GetEndColor();
	particleEndColor.z = _wtof(inputStr);
	GetTarget()->Particle()->SetEndColor(particleEndColor);
}


void CParticleDlg::OnEnSetfocusEndColorB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEndColorB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeEndColorA()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	endColorA.GetWindowTextW(inputStr);

	Vec4 particleEndColor = GetTarget()->Particle()->GetEndColor();
	particleEndColor.w = _wtof(inputStr);
	GetTarget()->Particle()->SetEndColor(particleEndColor);
}


void CParticleDlg::OnEnSetfocusEndColorA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEndColorA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeStartScale()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	startScale.GetWindowTextW(inputStr);

	float particleStartScale = GetTarget()->Particle()->GetStartScale();
	particleStartScale = _wtof(inputStr);
	GetTarget()->Particle()->SetStartScale(particleStartScale);
}


void CParticleDlg::OnEnSetfocusStartScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusStartScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeEndScale()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	endScale.GetWindowTextW(inputStr);

	float particleEndScale = GetTarget()->Particle()->GetEndScale();
	particleEndScale = _wtof(inputStr);
	GetTarget()->Particle()->SetEndScale(particleEndScale);
}


void CParticleDlg::OnEnSetfocusEndScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEndScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeStartSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	minSpeed.GetWindowTextW(inputStr);

	float particleStartSpeed = GetTarget()->Particle()->GetMinSpeed();
	particleStartSpeed = _wtof(inputStr);
	GetTarget()->Particle()->SetMinSpeed(particleStartSpeed);
}


void CParticleDlg::OnEnSetfocusStartSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusStartSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeEndSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	maxSpeed.GetWindowTextW(inputStr);

	float particleEndSpeed = GetTarget()->Particle()->GetMaxSpeed();
	particleEndSpeed = _wtof(inputStr);
	GetTarget()->Particle()->SetMaxSpeed(particleEndSpeed);
}


void CParticleDlg::OnEnSetfocusEndSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusEndSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeMinLifeTime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	minLifeTime.GetWindowTextW(inputStr);

	float particleMinLifeTime = GetTarget()->Particle()->GetMinLifeTime();
	particleMinLifeTime = _wtof(inputStr);
	GetTarget()->Particle()->SetMinLifeTime(particleMinLifeTime);
}


void CParticleDlg::OnEnSetfocusMinLifeTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusMinLifeTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeMaxLifeTime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	maxLifeTime.GetWindowTextW(inputStr);

	float particleMaxLifeTime = GetTarget()->Particle()->GetMaxLifeTime();
	particleMaxLifeTime = _wtof(inputStr);
	GetTarget()->Particle()->SetMaxLifeTime(particleMaxLifeTime);
}


void CParticleDlg::OnEnSetfocusMaxLifeTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusMaxLifeTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeFrequencyTime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	frequencyTime.GetWindowTextW(inputStr);

	float particleFrequencyTime = GetTarget()->Particle()->GetFrequency();
	particleFrequencyTime = _wtof(inputStr);
	GetTarget()->Particle()->SetFrequency(particleFrequencyTime);
}


void CParticleDlg::OnEnSetfocusFrequencyTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusFrequencyTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnEnChangeMaxCount()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString inputStr;
	maxParticleCount.GetWindowTextW(inputStr);

	float particleMaxParticleCount = GetTarget()->Particle()->GetMaxParticleCount();
	particleMaxParticleCount = _wtof(inputStr);
	GetTarget()->Particle()->SetMaxParticleCount(particleMaxParticleCount);
}


void CParticleDlg::OnEnSetfocusMaxCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CParticleDlg::OnEnKillfocusMaxCount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = false;
}


void CParticleDlg::OnBnClickedTexture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

	vector<CString> vecResName;

	for (const auto& pair : mapRes)
	{
		vecResName.push_back(pair.second->GetName().c_str());
	}

	CListDlg dlg(L"Texture", vecResName);
	int iRet = dlg.DoModal();

	if (IDOK == iRet)
	{
		CString strSelect = dlg.GetSelectItem();
		CResPtr<CTexture> findTexture = CResMgr::GetInst()->FindRes<CTexture>(strSelect.GetBuffer());
		GetTarget()->Particle()->SetParticleTexture(findTexture);
	}
}
