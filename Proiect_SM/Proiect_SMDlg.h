
// Proiect_SMDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CProiect_SMDlg dialog
class CProiect_SMDlg : public CDialogEx
{
// Construction
public:
	CProiect_SMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROIECT_SM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Add_Item_Col1();
	CListCtrl Magenta1;
	afx_msg void Add_Item_Col2();
};
