#pragma once


// generateNUmbers dialog

class generateNUmbers : public CDialogEx
{
	DECLARE_DYNAMIC(generateNUmbers)

public:
	generateNUmbers(CWnd* pParent = NULL);   // standard constructor
	virtual ~generateNUmbers();

// Dialog Data
	enum { IDD = IDD_PROIECT_SM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
