
// testmfc3View.cpp : Ctestmfc3View Ŭ������ ����

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "testmfc3.h"
#endif

#include "testmfc3Doc.h"
#include "testmfc3View.h"

#include "TextOutDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// Ctestmfc3View

IMPLEMENT_DYNCREATE(Ctestmfc3View, CView)

BEGIN_MESSAGE_MAP(Ctestmfc3View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ctestmfc3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_OPEN, &Ctestmfc3View::OnFileOpen)
	ON_COMMAND(ID_Edit_music, &Ctestmfc3View::OnEditmusic)
	ON_COMMAND(ID_Start_music, &Ctestmfc3View::OnStartmusic)
END_MESSAGE_MAP()

// Ctestmfc3View ����/�Ҹ�

Ctestmfc3View::Ctestmfc3View()
	
	: m_nCheckMiss(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	for (int i = 0; i < 6; i++) 
		count[i] = 0;
	
	end = false;
	
	Music_Path_1.Empty(); //(CString)"C:\\Users\\Gram\\Desktop\\SLAMDUNK.wav";
	pFileName = _T("no"); //_T("SLAMDUNK.txt");
		
	Hit_dd = 0;
	sx1 = 20;	sx2 = 80;	
	dx1 = 290;	dx2 = 350;	
	fx1 = 560;	fx2 = 620;		
	jx1 = 830;  jx2 = 890;	
	kx1 = 1100; kx2 = 1160;
	lx1 = 1370; lx2 = 1430;

}


Ctestmfc3View::~Ctestmfc3View()
{
}

BOOL Ctestmfc3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	return CView::PreCreateWindow(cs);
}

// Ctestmfc3View �׸���

void Ctestmfc3View::OnDraw(CDC* pDC)
{
	
	CRect rect;
	CDC dubleBfDC;
	CBitmap *pOldBitmap, bitmap;
	
	GetClientRect(&rect);
	
	dubleBfDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	
	pOldBitmap = dubleBfDC.SelectObject(&bitmap);
	dubleBfDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	ImageSet(&dubleBfDC);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dubleBfDC, 0, 0, SRCCOPY);
	
	dubleBfDC.SelectObject(pOldBitmap);
	dubleBfDC.DeleteDC();
	bitmap.DeleteObject();
	
}

// Ctestmfc3View �μ�

void Ctestmfc3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void Ctestmfc3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ctestmfc3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// Ctestmfc3View ����

#ifdef _DEBUG
void Ctestmfc3View::AssertValid() const
{
	CView::AssertValid();
}

void Ctestmfc3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctestmfc3Doc* Ctestmfc3View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctestmfc3Doc)));
	return (Ctestmfc3Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctestmfc3View �޽��� ó����

void Ctestmfc3View::Ellipse_make(CDC* pDC, int next, int x1)
{
	pDC->Ellipse(x1, flow + next, x1+130, flow + 60 + next);	//���߿� thread_d�� �����ϴ��� ����.
}

void Ctestmfc3View::Ellipse_color(CDC* pDC, int next, int x, int y, int check)
{
	//x2 ���� �Է� y�� y2����
	CBrush brush;
	if (check == 1)
		brush.CreateSolidBrush(RGB(255, 0, 0));
	else if(check == 2)
		brush.CreateSolidBrush(RGB(0, 0, 255));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	pDC->Ellipse(x - 60, y + next, x + 70, y +60+ next);
	pDC->SelectObject(oldBrush);
}

void Ctestmfc3View::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Ctestmfc3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);

	switch (nChar)
	{
		/*case VK_UP:	//ȭ��ǥ ��
			mode = 1;		//edit mode�� �Ѿ��.
			Edit_init();
			break;
		case VK_DOWN:	//ȭ��ǥ �Ʒ�
			mode = 0;		// ������� �Ѿ��.
			break;
		case 0x31: // '1'Ű
			pMainDlg->StartDefault();
			end = false;
			if (mode == 0) set_ready();
			music();
			MakeCircle();
			//exit(1);
			break;*/
		case 0x34: // '4'Ű
			if (mode == 1) {
				Write_File();
				Write_music(arr_s, &count[0]); Write_music(arr_d, &count[1]);
				Write_music(arr_f, &count[2]); Write_music(arr_j, &count[3]);
				Write_music(arr_k, &count[4]); Write_music(arr_l, &count[5]);
				Write_end();
				AfxMessageBox(_T("���� �Ϸ�"));
				end = true;  PlaySound(NULL, AfxGetInstanceHandle(), NULL); // �뷡 ����
				mode = 2;
			}
			else {
				AfxMessageBox(_T("'���� �ϱ�'�� �����ž� �մϴ�."));
			}
			break;
		/*case 0x35: // '5'
			Read_music();
			break;*/
		case 0x53: // S Ű
			if (mode==1) Edit_music(arr_s, &count[0]);
			else if (mode==0) HIt_func(grade_ss, 's', count[0]);
			break;
		case 0x44: // D Ű
			if (mode==1) Edit_music(arr_d, &count[1]);
			else if (mode==0) HIt_func(grade_dd, 'd', count[1]);
			break;
		case 0x46: // F Ű
			if (mode==1) Edit_music(arr_f, &count[2]);
			else if (mode==0) HIt_func(grade_ff, 'f', count[2]);
			break;
		case 0x4A: // J Ű
			if (mode==1) Edit_music(arr_j, &count[3]);
			else if (mode==0) HIt_func(grade_jj, 'j', count[3]);
			break;
		case 0x4B: // K Ű
			if (mode == 1)  Edit_music(arr_k, &count[4]);
			else if (mode==0) HIt_func(grade_kk, 'k', count[4]);
			break;
		case 0x4C: // L Ű
			if (mode==1) Edit_music(arr_l, &count[5]);
			else if (mode==0) HIt_func(grade_ll, 'l', count[5]);
			break;
		case 0x51: // Q Ű
			end = true;  PlaySound(NULL, AfxGetInstanceHandle(), NULL); // �뷡 ����
			break;
		/*case 0x52: // r Ű
			end = false;
			break;*/
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void Ctestmfc3View::music()
{
	PlaySound(Music_Path_1, AfxGetInstanceHandle(), SND_ASYNC); // �뷡 ��� ... �񵿱⼺															 
}

void Ctestmfc3View::set_ready()
{
	RECT rect;
	GetClientRect(&rect);
	int bottom = rect.bottom;

	for (int i = 0; i < count[0]; i++)
		next_ss[i] = bottom - tape_group[0][i];
	for (int i = 0; i < count[1]; i++)
		next_dd[i] = bottom - tape_group[1][i];
	for (int i = 0; i < count[2]; i++)
		next_ff[i] = bottom - tape_group[2][i];
	for (int i = 0; i < count[3]; i++)
		next_jj[i] = bottom - tape_group[3][i];
	for (int i = 0; i < count[4]; i++)
		next_kk[i] = bottom - tape_group[4][i];
	for (int i = 0; i < count[5]; i++)
		next_ll[i] = bottom - tape_group[5][i];

	flow = 0;
	max_count = largest_count(count);
	for (int i = 0; i < count[0]; i++) {
		grade_ss[0][i] = tape_group[0][i] - 60;
		grade_ss[1][i] = tape_group[0][i];
		grade_ss[2][i] = 0;
	}
	for (int i = 0; i < count[1]; i++) {
		grade_dd[0][i] = tape_group[1][i] - 60;
		grade_dd[1][i] = tape_group[1][i];
		grade_dd[2][i] = 0;
	}
	for (int i = 0; i < count[2]; i++) {
		grade_ff[0][i] = tape_group[2][i] - 60;
		grade_ff[1][i] = tape_group[2][i];
		grade_ff[2][i] = 0;
	}
	for (int i = 0; i < count[3]; i++) {
		grade_jj[0][i] = tape_group[3][i] - 60;
		grade_jj[1][i] = tape_group[3][i];
		grade_jj[2][i] = 0;
	}
	for (int i = 0; i < count[4]; i++) {
		grade_kk[0][i] = tape_group[4][i] - 60;
		grade_kk[1][i] = tape_group[4][i];
		grade_kk[2][i] = 0;
	}
	for (int i = 0; i < count[5]; i++) {
		grade_ll[0][i] = tape_group[5][i] - 60;
		grade_ll[1][i] = tape_group[5][i];
		grade_ll[2][i] = 0;
	}

	scheck = 0; dcheck = 0; fcheck = 0;
	jcheck = 0; kcheck = 0; lcheck = 0;
}

void Ctestmfc3View::MakeCircle()
{
	CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
	RECT rect;
	GetClientRect(&rect);
	bool finish = false;
	
	while (true)
	{
		flow += 6;

		sred_flow += 6; sblue_flow += 6;
		dred_flow += 6; dblue_flow += 6;
		fred_flow += 6; fblue_flow += 6;
		jred_flow += 6; jblue_flow += 6;
		kred_flow += 6; kblue_flow += 6;
		lred_flow += 6; lblue_flow += 6;

		Invalidate(false);
		Wait(1);
		
		/*
		if (mode == 0 && MaxLength() == 0) {
			AfxMessageBox(_T("�뷡������ �Ϸ�Ǿ����� Ȯ���� �ʿ��մϴ�."));
			return;
		}*/
		if (end == true)
		{
			PlaySound(NULL, AfxGetInstanceHandle(), NULL);
			break;
		}
		else if (mode == 0 && flow >= MaxLength()+300) {
			PlaySound(NULL, AfxGetInstanceHandle(), NULL);
			finish = true;
			break;
		}
		
	}
	if ( mode == 0 && flow >= MaxLength()+300 && finish == true )
		pMainDlg->MakeGameOverDlg();
}

void Ctestmfc3View::HIt_func(int grade[][500], char key, int count)
{
	int i = 0;
	//CClientDC dc(this);
	CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
	int diff = 0;
	while (true) {
		diff = (grade[0][i] + grade[1][i]) / 2;
		if (( diff-60 <= flow) && ( flow <= diff+60) ) {
			if (grade[2][i] == 0) {
				if (( diff-50 <= flow && flow <= diff-20 )) {
				
					if (key == 's') {
						scheck = 1;
						sred = next_ss[i];
						sred_flow = flow;
						pMainDlg->HitScore(100);
					}
					else if (key == 'd') {
						dcheck = 1;
						dred = next_dd[i];
						dred_flow = flow;
						pMainDlg->HitScore(100);
					}
					else if (key == 'f') {
						fcheck = 1;
						fred = next_ff[i];
						fred_flow = flow;
						pMainDlg->HitScore(100);
					}
					else if (key == 'j') {
						jcheck = 1;
						jred = next_jj[i];
						jred_flow = flow;
						pMainDlg->HitScore(100);
					}
					else if (key == 'k') {
						kcheck = 1;
						kred = next_kk[i];
						kred_flow = flow;
						pMainDlg->HitScore(100);
					}
					else if (key == 'l') {
						lcheck = 1;
						lred = next_ll[i];
						lred_flow = flow;
						pMainDlg->HitScore(100);
					}

					grade[2][i]++;
					break;
				}
				else {

					if (key == 's') {
						scheck = 2;
						sblue = next_ss[i];
						sblue_flow = flow;
						pMainDlg->HitScore(50);
					}
					else if (key == 'd') {
						dcheck = 2;
						dblue = next_dd[i];
						dblue_flow = flow;
						pMainDlg->HitScore(50);
					}
					else if (key == 'f') {
						fcheck = 2;
						fblue = next_ff[i];
						fblue_flow = flow;
						pMainDlg->HitScore(50);
					}
					else if (key == 'j') {
						jcheck = 2;
						jblue = next_jj[i];
						jblue_flow = flow;
						pMainDlg->HitScore(50);
					}
					else if (key == 'k') {
						kcheck = 2;
						kblue = next_kk[i];
						kblue_flow = flow;
						pMainDlg->HitScore(50);
					}
					else if (key == 'l') {
						lcheck = 2;
						lblue = next_ll[i];
						lblue_flow = flow;
						pMainDlg->HitScore(50);
					}

					grade[2][i]++;
					break;
				}
			}
			else {
				if (key == 's')
				{
					pMainDlg->MissCount(1);
					scheck = 3;
				}
				else if (key == 'd') 
				{
					pMainDlg->MissCount(1);
					dcheck = 3;
				}
				else if (key == 'f') 
				{
					pMainDlg->MissCount(1);
					fcheck = 3;
				}
				else if (key == 'j') 
				{
					pMainDlg->MissCount(1);
					jcheck = 3;
				}
				else if (key == 'k') 
				{
					pMainDlg->MissCount(1);
					kcheck = 3;
				}
				else if (key == 'l') 
				{
					pMainDlg->MissCount(1);
					lcheck = 3;
				}
				break;
			}
		}
		else if (i == count) {
			if (key == 's')
			{
				pMainDlg->MissCount(1);
				scheck = 3;
			}
			else if (key == 'd')
			{
				pMainDlg->MissCount(1);
				dcheck = 3;
			}
			else if (key == 'f')
			{
				pMainDlg->MissCount(1);
				fcheck = 3;
			}
			else if (key == 'j')
			{
				pMainDlg->MissCount(1);
				jcheck = 3;
			}
			else if (key == 'k')
			{
				pMainDlg->MissCount(1);
				kcheck = 3;
			}
			else if (key == 'l')
			{
				pMainDlg->MissCount(1);
				lcheck = 3;
			}
			break;
		}

		i++;
	}
}


void Ctestmfc3View::Edit_init() 
{	
	for (int i = 0; i < 6; i++)
		count[i] = 0;
	flow = 0;
}
void Ctestmfc3View::Edit_music(int* arr, int * count)
{
	arr[*count] = flow;
	(*count)++;
}
void Ctestmfc3View::Write_File()
{
	if (!fp.Open(pFileName, CFile::modeCreate | CFile::modeWrite |
		CFile::typeBinary /*| CFile::modeNoTruncate*/))
	{
		TRACE(_T("Unable to open file\n"));
	}
}
void Ctestmfc3View::Write_end()
{
	fp.Close();
}
void Ctestmfc3View::Write_music(int* arr, int * count)
{
	CString strNull = _T("\n");
	CString tape;
	
	fp.SeekToEnd();

	tape.Format(_T("%d"), *count);

	fp.WriteString(tape);
	fp.WriteString(strNull);
	for (int i = 0; i < *count; i++) {
		
		tape.Format(_T("%d"), arr[i]);
		fp.WriteString(tape);
		fp.WriteString(strNull);
		/*if(i == *count - 1)
			AfxMessageBox(_T("���� �Ϸ�"));*/
	}
}



void Ctestmfc3View::Read_music()
{
	CString tape;
	int real_tape = 1;
	
	if (!fp.Open(pFileName, CFile::modeRead | CFile::shareExclusive | CFile::typeBinary))
	{
		AfxMessageBox(_T("���� ��尡 ���������� �ʽ��ϴ�.\n������ ���ּ���!"));
		return;
	}
	
	for (int i = 0; i < 6; i++) {
		fp.ReadString(tape);
		real_tape = _ttoi(tape);
		count[i] = real_tape;	//count[0~5] �����ؼ� �迭�� ���Ƶ���.

		for (int j = 0; j < count[i]; j++) {
			fp.ReadString(tape);
			real_tape = _ttoi(tape);
			tape_group[i][j] = real_tape;
		}
	}
	//AfxMessageBox(_T("�б� �Ϸ�"));
	fp.Close();
}



void Ctestmfc3View::OnFileOpen()
{
	char name_filter[] = "All Files (*.*)|*.*|wav Files (*.wav)|*.cpp|Text Files (*.txt)|*.txt||";

	CFileDialog ins_dlg(TRUE, _T("wav"), _T("*.wav"), OFN_HIDEREADONLY, name_filter, NULL, 0, TRUE);

	ins_dlg.m_ofn.nFilterIndex = 2;

	if (ins_dlg.DoModal() == IDOK) {
		Music_Path_1 = ins_dlg.GetPathName();
		
		CString a = ins_dlg.GetFileTitle();
		a.Append(_T(".txt"));
		pFileName = _tcsdup(a);
		
		AfxMessageBox(_T("�뷡 ������ �Ϸ��߽��ϴ�!"));
		Read_music();
	}
	else {
		::MessageBox(NULL, _T("���� ���⸦ ����Ͽ����ϴ�."), _T("�˸�"), MB_ICONINFORMATION);
	}
	
}



void Ctestmfc3View::ImageSet(CDC* pDC)
{
	RECT rect;
	GetClientRect(&rect);
	int bot = rect.bottom;

	pDC->Rectangle(0, rect.bottom - 62, 1800, rect.bottom);

	for (int j = 0; j <= 1350; j += 270) // ���� �� 
		initCircle(pDC, j);
	if (mode == 0) {
		for (int i = 0; i < max_count; i++) {
			Ellipse_make(pDC, next_ss[i], sx1);

			if (scheck == 1) {
				Ellipse_color(pDC, sred, sx2, sred_flow, 1);
				pDC->TextOut((sx1 + 140), bot - 35, CString("PERFECT"));
			}
			else if (scheck == 2) {
				Ellipse_color(pDC, sblue, sx2, sblue_flow, 2);
				pDC->TextOut((sx1 + 140), bot - 35, CString("GOOD"));
			}
			else if (scheck == 3) {
				pDC->TextOut((sx1 + 140), bot - 35, CString("MISS"));
			}


			Ellipse_make(pDC, next_dd[i], dx1);

			if (dcheck == 1) {
				Ellipse_color(pDC, dred, dx2, dred_flow, 1);
				pDC->TextOut((dx1 + 140), bot - 35, CString("PERFECT"));
			}
			else if (dcheck == 2) {
				Ellipse_color(pDC, dblue, dx2, dblue_flow, 2);
				pDC->TextOut((dx1 + 140), bot - 35, CString("GOOD"));
			}
			else if (dcheck == 3) {
				pDC->TextOut((dx1 + 140), bot - 35, CString("MISS"));
			}


			Ellipse_make(pDC, next_ff[i], fx1);

			if (fcheck == 1) {
				Ellipse_color(pDC, fred, fx2, fred_flow, 1);
				pDC->TextOut((fx1 + 140), bot - 35, CString("PERFECT"));
			}
			else if (fcheck == 2) {
				Ellipse_color(pDC, fblue, fx2, fblue_flow, 2);
				pDC->TextOut((fx1 + 140), bot - 35, CString("GOOD"));
			}
			else if (fcheck == 3) {
				pDC->TextOut((fx1 + 140), bot - 35, CString("MISS"));
			}


			Ellipse_make(pDC, next_jj[i], jx1);

			if (jcheck == 1) {
				Ellipse_color(pDC, jred, jx2, jred_flow, 1);
				pDC->TextOut((jx1 + 140), bot - 35, CString("PERFECT"));
			}
			else if (jcheck == 2) {
				Ellipse_color(pDC, jblue, jx2, jblue_flow, 2);
				pDC->TextOut((jx1 + 140), bot - 35, CString("GOOD"));
			}
			else if (jcheck == 3) {
				pDC->TextOut((jx1 + 140), bot - 35, CString("MISS"));
			}


			Ellipse_make(pDC, next_kk[i], kx1);

			if (kcheck == 1) {
				Ellipse_color(pDC, kred, kx2, kred_flow, 1);
				pDC->TextOut((kx1 + 140), bot - 35, CString("PERFECT"));
			}
			else if (kcheck == 2) {
				Ellipse_color(pDC, kblue, kx2, kblue_flow, 2);
				pDC->TextOut((kx1 + 140), bot - 35, CString("GOOD"));
			}
			else if (kcheck == 3) {
				pDC->TextOut((kx1 + 140), bot - 35, CString("MISS"));
			}


			Ellipse_make(pDC, next_ll[i], lx1);

			if (lcheck == 1) {
				Ellipse_color(pDC, lred, lx2, lred_flow, 1);
				pDC->TextOut((lx1 + 140), bot - 35, CString("PERFECT"));
			}
			else if (lcheck == 2) {
				Ellipse_color(pDC, lblue, lx2, lblue_flow, 2);
				pDC->TextOut((lx1 + 140), bot - 35, CString("GOOD"));
			}
			else if (lcheck == 3) {
				pDC->TextOut((lx1 + 140), bot - 35, CString("MISS"));
			}
		}
	}
}

void Ctestmfc3View::initCircle(CDC* pDC, int n)
{
	RECT rect;
	GetClientRect(&rect);

	pDC->Ellipse(20 + n, rect.bottom - 60, 150 + n, rect.bottom - 1);
	if (n == 0)
		pDC->TextOut(80 + n, rect.bottom - 40, CString("S"));
	if (n == 270)
		pDC->TextOut(80 + n, rect.bottom - 40, CString("D"));
	if (n == 540)
		pDC->TextOut(80 + n, rect.bottom - 40, CString("F"));
	if (n == 810)
		pDC->TextOut(80 + n, rect.bottom - 40, CString("J"));
	if (n == 1080)
		pDC->TextOut(80 + n, rect.bottom - 40, CString("K"));
	if (n == 1350)
		pDC->TextOut(80 + n, rect.bottom - 40, CString("L"));

}


int Ctestmfc3View::largest_count(int count[])
{
	int temp=0;
	
	for (int k = 0; k < 6; k++)	{
		if (count[k] > temp)
			temp = count[k];
	}
	return temp;
}


int Ctestmfc3View::MaxLength()
{
		int length[6] = {
			grade_ss[0][count[0] - 1] , grade_dd[0][count[1] - 1],
			grade_ff[0][count[2] - 1], grade_jj[0][count[3] - 1],
			grade_kk[0][count[4] - 1], grade_ll[0][count[5] - 1]
		};
		int temp = 0;

		for (int i = 0; i < 6; i++) {
			if (temp < length[i])
				temp = length[i];
		}

		return temp;
}


void Ctestmfc3View::OnEditmusic()
{
	if (!Music_Path_1.IsEmpty()) {
		end = true;
		CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);

		pMainDlg->m_listRecord.ResetContent();
		pMainDlg->m_listRecord.AddString(_T("��������Դϴ�."));
		pMainDlg->m_listRecord.AddString(_T("������ ������ "));
		pMainDlg->m_listRecord.AddString(_T("4���� �����ּ���."));

		mode = 1;		//edit mode�� �Ѿ��. 
		Edit_init();
		scheck = 0; dcheck = 0; fcheck = 0;
		jcheck = 0; kcheck = 0; lcheck = 0;

		pMainDlg->StartDefault();
		end = false;
		Wait(1200);
		music();
		MakeCircle();
	}
	else {
		AfxMessageBox(_T("�뷡�� �������ּ���."));
	}
}


void Ctestmfc3View::OnStartmusic()
{
	if (!Music_Path_1.IsEmpty()) {
		end = true;
		CTextOutDlg* pMainDlg = (CTextOutDlg*)((CMainFrame *)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
		pMainDlg->m_listRecord.ResetContent();
		pMainDlg->m_listRecord.AddString(_T("���� ����!"));
		Read_music();
		mode = 0;
		pMainDlg->StartDefault();
		end = false;
		Wait(1200);
		set_ready();
		music();
		MakeCircle();
	}
	else {
		AfxMessageBox(_T("�뷡�� �������ּ���."));
	}
}
