#pragma once


// CGameOver ��ȭ �����Դϴ�.

class CGameOver : public CDialogEx
{
	DECLARE_DYNAMIC(CGameOver)

public:
	CGameOver(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGameOver();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CString m_strName;
	int m_nScore;

};
