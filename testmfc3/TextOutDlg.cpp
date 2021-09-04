// TextOutDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "testmfc3.h"
#include "TextOutDlg.h"

#include "MainFrm.h"



// CTextOutDlg

IMPLEMENT_DYNCREATE(CTextOutDlg, CFormView)

CTextOutDlg::CTextOutDlg()
	: CFormView(IDD_FORMVIEW)
	, m_nScore(0)
	, m_pop(0)
	, m_nMisscnt(0)
{

}

CTextOutDlg::~CTextOutDlg()
{
}

void CTextOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECORD, m_listRecord);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_nScore);
	DDX_Control(pDX, IDC_BUTTON_PLAY, play_button);
	//  DDX_Control(pDX, IDC_PROGRESS1, m_Proctl);
	DDX_Control(pDX, IDC_PROGRESS1, m_Proctl1);
	DDX_Control(pDX, IDC_PROGRESS2, m_Proctl2);
	DDX_Control(pDX, IDC_PROGRESS3, m_Proctl3);
	DDX_Control(pDX, IDC_PROGRESS4, m_Proctl4);
	DDX_Control(pDX, IDC_PROGRESS5, m_Proctl5);
}

BEGIN_MESSAGE_MAP(CTextOutDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CTextOutDlg::OnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CTextOutDlg::OnClickedButtonPlay)
END_MESSAGE_MAP()


// CTextOutDlg �����Դϴ�.

#ifdef _DEBUG
void CTextOutDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTextOutDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTextOutDlg �޽��� ó�����Դϴ�.


void CTextOutDlg::SaveRecord()
{
	setlocale(LC_ALL, "korean");
	UpdateData(TRUE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString name;
	CString strscore;
	CString* strscoreary;
	CString* nameary;
	LPCTSTR* fscoreary;
	LPCTSTR* fnameary;
	int* scoreary;
	CString text;
	CString strnull = _T("\n");
	LPCTSTR fname;
	LPCTSTR fnull;
	LPCTSTR fscore;
	CStdioFile f1;
	TCHAR* pFileName = _T("record.txt");
	int score, i;
	int cnt = 0, cnt2;
	name = m_DlgGameOver.m_strName;
	name.Append(_T("\n"));
	fname = name;
	score = m_DlgGameOver.m_nScore;
	strscore.Format(_T("%d"), score);
	fscore = strscore;
	fnull = strnull;
	if (!f1.Open(pFileName, CFile::modeCreate | CFile::modeWrite |
		CFile::typeBinary | CFile::modeNoTruncate))
	{
		TRACE(_T("Unable to open file\n"));
	}
	f1.SeekToEnd();
	f1.WriteString(fscore);
	f1.WriteString(fnull);
	f1.WriteString(fname);
	UpdateData(FALSE);
	f1.Close();

	if (!f1.Open(pFileName, CFile::modeRead | CFile::shareExclusive | CFile::typeBinary))
	{
		TRACE(_T("Unable to open file\n"));
	}
	while (f1.ReadString(text))
	{
		cnt++;
	}
	cnt = cnt / 2;
	strscoreary = new CString[cnt];
	scoreary = new int[cnt];
	nameary = new CString[cnt];
	fscoreary = new LPCTSTR[cnt];
	fnameary = new LPCTSTR[cnt];
	f1.SeekToBegin();
	cnt2 = 1;

	while (f1.ReadString(text)) // Ȧ������ ���ڹ迭�� ¦������ �̸��迭�� �ֱ�
	{
		if (cnt2 % 2 == 1)
		{

			strscoreary[cnt2 / 2] = text;
		}
		else
		{
			nameary[cnt2 / 2 - 1] = text;
		}
		cnt2++;
	}
	for (i = 0; i < cnt; i++)
	{
		scoreary[i] = _ttoi(strscoreary[i]); // cstring to int
	}
	if (cnt > 1)
	{
		qsort(cnt, scoreary, strscoreary, nameary);
	}
	m_listRecord.ResetContent();
	for (i = 0; i < cnt; i++)
	{
		fnameary[i] = nameary[i];
		fscoreary[i] = strscoreary[i];
	}
	for (i = 1; i <= 2 * cnt; i++)
	{
		if (i % 2 == 1)
		{
			m_listRecord.AddString(fscoreary[i / 2]);
		}
		else
		{
			m_listRecord.AddString(fnameary[i / 2 - 1]);
		}
	}

	f1.Close();
	delete[] strscoreary;
	delete[] nameary;
	delete[] scoreary;
	delete[] fnameary;
	delete[] fscoreary;
}


void CTextOutDlg::MakeGameOverDlg()
{
	m_DlgGameOver.m_nScore = m_nScore;
	m_DlgGameOver.DoModal();
	while (1)
	{
		if (m_pop == 1)
		{
			SaveRecord();
			break;
		}
		if (m_pop == 2)
		{
			break;
		}
	}
	m_pop = 0;
}


void CTextOutDlg::qsort(int cnt, int* scoreary, CString* strscoreary, CString* nameary)
{
	int i, j, k, changecnt, min, int_temp;
	CString str_temp;
	for (i = 0; i < cnt - 1; i++)
	{
		min = scoreary[i];
		changecnt = 0;
		for (j = i + 1; j < cnt; j++)
		{
			if (min < scoreary[j])
			{
				min = scoreary[j];
				k = j;
				changecnt++;
			}
		}
		if (changecnt != 0)
		{
			int_temp = scoreary[i];
			str_temp = nameary[i];
			scoreary[i] = scoreary[k];
			scoreary[k] = int_temp;
			nameary[i] = nameary[k];
			nameary[k] = str_temp;
		}
	}
	for (i = 0; i < cnt; i++)
	{
		strscoreary[i].Format(_T("%d"), scoreary[i]);
	}
}


void CTextOutDlg::HitScore(int score)
{
	m_nScore += score;
	UpdateData(false);
}


void CTextOutDlg::MissCount(int cnt)
{
	m_nMisscnt += cnt;
	if (m_nMisscnt == 1)
	{
		m_Proctl1.SetPos(0);
	}
	if (m_nMisscnt == 2)
	{
		m_Proctl2.SetPos(0);
	}
	if (m_nMisscnt == 3)
	{
		m_Proctl3.SetPos(0);
	}
	if (m_nMisscnt == 4)
	{
		m_Proctl4.SetPos(0);
	}
	//�������� down
	if (m_nMisscnt == 5)
	{
		m_Proctl5.SetPos(0);
		PlaySound(NULL, AfxGetInstanceHandle(), NULL);
		MakeGameOverDlg();
		CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
		Ctestmfc3View* pView = (Ctestmfc3View*)pFrame->GetActiveView();
		pView->end = true;
	}
}



void CTextOutDlg::StartDefault()
{
	m_nScore = 0;
	m_nMisscnt = 0;

	//ü�� ������ �ʱ�ȭ
	m_Proctl1.SetBarColor(RGB(255, 0, 0));
	m_Proctl1.SetRange(0, 100);
	m_Proctl1.SetPos(100);


	m_Proctl2.SetBarColor(RGB(255, 0, 0));
	m_Proctl2.SetRange(0, 100);
	m_Proctl2.SetPos(100);


	m_Proctl3.SetBarColor(RGB(255, 0, 0));
	m_Proctl3.SetRange(0, 100);
	m_Proctl3.SetPos(100);


	m_Proctl4.SetBarColor(RGB(255, 0, 0));
	m_Proctl4.SetRange(0, 100);
	m_Proctl4.SetPos(100);


	m_Proctl5.SetBarColor(RGB(255, 0, 0));
	m_Proctl5.SetRange(0, 100);
	m_Proctl5.SetPos(100);



	//������ ������
	UpdateData(FALSE);
}


void CTextOutDlg::OnClickedButtonEdit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listRecord.ResetContent();
	m_listRecord.AddString(_T("�뷡����(.wav)��"));
	m_listRecord.AddString(_T("�߰��� ��"));
	m_listRecord.AddString(_T("�ڽ��� ���ϴ´��"));
	m_listRecord.AddString(_T("Ű�� �Է��Ͽ� ��������"));
	m_listRecord.AddString(_T("��带 �����մϴ�."));
	m_listRecord.AddString(_T("�����Ϸ� ��"));
	m_listRecord.AddString(_T("4���� �����ּ���."));

}


void CTextOutDlg::OnClickedButtonPlay()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_listRecord.ResetContent();
	m_listRecord.AddString(_T("�뷡����(.wav)��"));
	m_listRecord.AddString(_T("�߰��� ��"));
	m_listRecord.AddString(_T("���۹�ưŬ����"));
	m_listRecord.AddString(_T("������ ���۵˴ϴ�."));
}
