
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

	void CProiect_SMDlg::generateNumbers(int length);
	void CProiect_SMDlg::initializeNumbers();

	void CProiect_SMDlg::insertionSort(int data[], int lenD);
	void CProiect_SMDlg::bubbleSort(int data[], int lenD);
	void CProiect_SMDlg::shellSort(int data[], int lenD);

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
	afx_msg void Process_Info();
	CListCtrl Magenta1;
	afx_msg void Compare();
	afx_msg void CPUID_Button();
	afx_msg void RTDSC_Button();
	afx_msg void OnBnClickedButton_PCI();
};
