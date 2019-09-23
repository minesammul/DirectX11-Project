// ResourceDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ResourceDlg.h"
#include "afxdialogex.h"

#include <ResMgr.h>
#include <PathMgr.h>
// ResourceDlg 대화 상자

IMPLEMENT_DYNAMIC(ResourceDlg, CDialogEx)

ResourceDlg::ResourceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESOURCEDLG, pParent),
	m_bInit(false)
{

}

ResourceDlg::~ResourceDlg()
{
}

void ResourceDlg::init()
{
	CString strContent = CPathMgr::GetResPath();

	LoadResource(strContent);

	// 항목 추가
	HTREEITEM arrItem[(UINT)RES_TYPE::END] = {
		AddItem(L"Material", nullptr, 0, TVI_LAST)
		, AddItem(L"Prefab", nullptr, 0, TVI_LAST)
		, AddItem(L"Mesh", nullptr, 0, TVI_LAST)
		, AddItem(L"Shader", nullptr, 0, TVI_LAST)
		, AddItem(L"Texture", nullptr, 0, TVI_LAST)
		, AddItem(L"Sound", nullptr, 0, TVI_LAST)
	};

	// ResMgr 에서 현재 로딩되어있는 리소스 목록을 가져온다.
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		const map<wstring, CResource*>& map = CResMgr::GetInst()->GetResources(RES_TYPE(i));

		for (const auto& pair : map)
		{
			CString strName = CPathMgr::GetFileName(pair.first.c_str());
			AddItem(strName, arrItem[i], (DWORD_PTR)pair.second, TVI_SORT);
		}
	}
}

void ResourceDlg::LoadResource(CString _strFolderPath)
{
	/*WIN32_FIND_DATA tData = {};
	HANDLE h = (HANDLE)FindFirstFile(_strFolderPath.GetBuffer(), &tData);
	UINT err = GetLastError();

	while (true)
	{
		if (FILE_ATTRIBUTE_DIRECTORY & tData.dwFileAttributes)
		{
			LoadResource(_strFolderPath + tData.cFileName);
		}
		else
		{
			const wchar_t* pExt = CPathMgr::GetExt(tData.cFileName);

			if (!wcscmp(pExt, L".png")
				|| !wcscmp(pExt, L".bmp")
				|| !wcscmp(pExt, L".jpg")
				|| !wcscmp(pExt, L".jpeg"))
			{
				wstring strKey = _strFolderPath + tData.cFileName;

				pTex = CResMgr::GetInst()->Load<CTexture>(strKey, strKey);
				tFrm.pTex = pTex;
				tFrm.vTerm = _fTerm;
				tFrm.vLT = Vec2(0.f, 0.f);
				tFrm.vSize = Vec2(1.f, 1.f);

				m_vecFrm.push_back(tFrm);
			}
			else if (!wcscmp(pExt, L".mp3")
				|| !wcscmp(pExt, L".ogg")
				|| !wcscmp(pExt, L".wav"))
			{

			}
			else if (!wcscmp(pExt, L".mtrl"))
			{

			}
			else if (!wcscmp(pExt, L".mdat"))
			{

			}
			else if (!wcscmp(pExt, L".prf"))
			{

			}
		}

		if (false == FindNextFile(h, &tData))
		{
			err = GetLastError();
			break;
		}
	}*/
}

HTREEITEM ResourceDlg::AddItem(CString _str, HTREEITEM _hParent, DWORD_PTR _dwData, HTREEITEM _hSortop)
{
	TVINSERTSTRUCT tInsert = {};

	tInsert.hParent = _hParent;
	tInsert.hInsertAfter = _hSortop;
	tInsert.item.pszText = _str.GetBuffer();
	tInsert.item.mask = TVIF_TEXT;

	HTREEITEM hItem = m_ctrlTree.InsertItem(&tInsert);
	m_ctrlTree.SetItemData(hItem, _dwData);

	return hItem;
}

void ResourceDlg::MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// 아이템 정보를 얻는다.
	wchar_t szName[255] = {};

	TV_ITEMW item = {};

	item.hItem = _hSrcItem;
	item.pszText = szName;
	item.cchTextMax = 255;
	item.mask = TVIF_TEXT | TVIF_HANDLE;

	m_ctrlTree.GetItem(&item);

	DWORD_PTR dwData = m_ctrlTree.GetItemData(_hSrcItem);

	// 얻어온 정보로 목적지의 자식으로 넣는다.
	HTREEITEM hCopyItem = AddItem(szName, _hDestItem, dwData, TVI_SORT);

	vector<HTREEITEM> vecChild;
	GetChildItem(_hSrcItem, vecChild);

	for (UINT i = 0; i < vecChild.size(); ++i)
	{
		MoveItem(vecChild[i], hCopyItem);
	}

	// 원본 아이템을 삭제한다.
	m_ctrlTree.DeleteItem(_hSrcItem);

	m_ctrlTree.Expand(_hDestItem, TVE_EXPAND);
}

void ResourceDlg::GetChildItem(HTREEITEM _hItem, vector<HTREEITEM>& _vecChild)
{
	// Item 에 자식이 없으면 리턴
	if (!m_ctrlTree.ItemHasChildren(_hItem))
		return;

	HTREEITEM hChildItem = m_ctrlTree.GetChildItem(_hItem);
	_vecChild.push_back(hChildItem);

	while (true)
	{
		hChildItem = m_ctrlTree.GetNextSiblingItem(hChildItem);

		if (nullptr == hChildItem)
			break;

		_vecChild.push_back(hChildItem);
	}
}

void ResourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);

	m_bInit = true;
}

void ResourceDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_bInit)
	{
		// Tree Control Size 를 Dialog Size 로 맞춘다.
		m_ctrlTree.SetWindowPos(nullptr, 0, 0, cx, cy, 0);
	}
}


BEGIN_MESSAGE_MAP(ResourceDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// ResourceDlg 메시지 처리기
