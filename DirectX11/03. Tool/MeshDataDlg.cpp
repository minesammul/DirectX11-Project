// MeshDataDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MeshDataDlg.h"
#include "afxdialogex.h"

#include <MeshData.h>
#include <ResMgr.h>
#include <GameObject.h>
#include <Animator3D.h>
#include <Transform.h>
#include <SceneMgr.h>
#include <Scene.h>

// CMeshDataDlg 대화 상자

IMPLEMENT_DYNAMIC(CMeshDataDlg, CDialogEx)

CMeshDataDlg::CMeshDataDlg(CWnd* pParent /*=nullptr*/)
	: CResInfoDlg(IDD_MESHDATADLG, pParent)
{

}

CMeshDataDlg::~CMeshDataDlg()
{
}

void CMeshDataDlg::SetResource(CResource * _pRes)
{
	CResInfoDlg::SetResource(_pRes);

	animationStartFrame.SetSel(0,-1);
	animationStartFrame.Clear();

	animationEndFrame.SetSel(0, -1);
	animationEndFrame.Clear();

	newAniName.SetSel(0, -1);
	newAniName.Clear();

	editCreateFBXObjectName.SetSel(0, -1);
	editCreateFBXObjectName.Clear();

	nowAnimationListCtrl.DeleteAllItems();

	vector<CResPtr<CMesh>> selectMeshs = ((CMeshData*)_pRes)->GetVectorMesh();

	for (int index = 0; index < selectMeshs[0]->GetAnimClip()->size(); index++)
	{
		CString aniName = (*selectMeshs[0]->GetAnimClip())[index].strAnimName.c_str();
		nowAnimationListCtrl.InsertItem(index, aniName);

		CString inputFrame;
		inputFrame.Format(L"%d", (*selectMeshs[0]->GetAnimClip())[index].iStartFrame);
		nowAnimationListCtrl.SetItemText(index, 1, inputFrame);

		inputFrame.Format(L"%d", (*selectMeshs[0]->GetAnimClip())[index].iEndFrame);
		nowAnimationListCtrl.SetItemText(index, 2, inputFrame);
	}
}

BOOL CMeshDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	nowAnimationListCtrl.InsertColumn(0, L"Name", LVCFMT_CENTER, 80);
	nowAnimationListCtrl.InsertColumn(1, L"Start Frame", LVCFMT_CENTER, 90);
	nowAnimationListCtrl.InsertColumn(2, L"End Frame", LVCFMT_CENTER, 90);
	return 0;
}

void CMeshDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, animationStartFrame);
	DDX_Control(pDX, IDC_EDIT2, animationEndFrame);
	DDX_Control(pDX, IDC_LIST3, nowAnimationListCtrl);
	DDX_Control(pDX, IDC_EDIT3, newAniName);
	DDX_Control(pDX, IDC_EDIT4, editCreateFBXObjectName);
}


BEGIN_MESSAGE_MAP(CMeshDataDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMeshDataDlg::OnBnClickedButtonNewAniInsert)
	ON_BN_CLICKED(IDC_BUTTON2, &CMeshDataDlg::OnBnClickedButtonCreateFBXObject)
END_MESSAGE_MAP()


// CMeshDataDlg 메시지 처리기


void CMeshDataDlg::OnBnClickedButtonNewAniInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString startFrameStr;
	animationStartFrame.GetWindowTextW(startFrameStr);

	CString endFrameStr;
	animationEndFrame.GetWindowTextW(endFrameStr);

	CString aniNameStr;
	newAniName.GetWindowTextW(aniNameStr);


	if (startFrameStr.IsEmpty() || endFrameStr.IsEmpty() || aniNameStr.IsEmpty())
	{
		return;
	}

	vector<CResPtr<CMesh>> selectMeshs = ((CMeshData*)GetRes())->GetVectorMesh();

	int startFrame = _ttoi(startFrameStr);
	int endFrame = _ttoi(endFrameStr);

	for (int index = 0; index < selectMeshs.size(); index++)
	{
		tMTAnimClip originAniData = selectMeshs[index]->GetAnimClip(0);

		vector<tMTAnimClip> newAniVector;
		newAniVector.assign(selectMeshs[index]->GetAnimClip()->begin(), selectMeshs[index]->GetAnimClip()->end());

		tMTAnimClip newAniData = originAniData;
		newAniData.iStartFrame = startFrame;
		newAniData.iEndFrame = endFrame;
		newAniData.iFrameLength = newAniData.iEndFrame - newAniData.iStartFrame + 1;

		int boneIndex = 0;
		while (true)
		{
			if ((*selectMeshs[index]->GetBones())[boneIndex].vecKeyFrame.empty() == false)
			{
				newAniData.dStartTime = (*selectMeshs[index]->GetBones())[boneIndex].vecKeyFrame[newAniData.iStartFrame].fTime;
				newAniData.dEndTime = (*selectMeshs[index]->GetBones())[boneIndex].vecKeyFrame[newAniData.iEndFrame].fTime;
				break;
			}
			boneIndex++;
		}
		newAniData.dTimeLength = newAniData.dEndTime - newAniData.dStartTime;
		newAniData.strAnimName = aniNameStr;

		newAniVector.push_back(newAniData);

		selectMeshs[index]->SetAnimClip(newAniVector);

		((CMeshData*)GetRes())->SetVectorMesh(selectMeshs[index], index);
	}

	((CMeshData*)GetRes())->Save();

}


void CMeshDataDlg::OnBnClickedButtonCreateFBXObject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString objectNameStr;
	editCreateFBXObjectName.GetWindowTextW(objectNameStr);

	if (objectNameStr.IsEmpty())
	{
		return;
	}
	
	CGameObject* pMeshObject = ((CMeshData*)GetRes())->Instantiate();

	for (int index = 0; index < pMeshObject->GetChild().size(); index++)
	{
		if (pMeshObject->GetChild()[index]->Animator3D()==nullptr)
		{
			continue;
		}

		pMeshObject->GetChild()[index]->Animator3D()->SetCurAnimClip(0);
	}

	pMeshObject->SetName(objectNameStr.GetBuffer());
	pMeshObject->Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));

	CSceneMgr::GetInst()->GetCurScene()->AddObject(L"Default", pMeshObject);
}
