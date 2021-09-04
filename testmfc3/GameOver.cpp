// GameOver.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "testmfc3.h"
#include "GameOver.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "TextOutDlg.h"

// CGameOver ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGameOver, CDialogEx)

CGameOver::CGameOver(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)

	, m_strName(_T(""))
	, m_nScore(0)
{

}

CGameOver::~CGameOver()
{
}

void CGameOver::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POPNAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_POPSCORE, m_nScore);
}


BEGIN_MESSAGE_MAP(CGameOver, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGameOver::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGameOver::OnBnClickedCancel)
	ON_WM_CREATE()

END_MESSAGE_MAP()


// CGameOver �޽��� ó�����Դϴ�.


void CGameOver::OnBnClickedOk()
{
	CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	pMainDlg->m_pop = 1;
	CDialogEx::OnOK();
}


void CGameOver::OnBnClickedCancel()
{
	CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
	pMainDlg->m_pop = 2;
	CDialogEx::OnCancel();
}


//int CGameOver::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
//	UpdateData(FALSE);
//	return 0;
//}





