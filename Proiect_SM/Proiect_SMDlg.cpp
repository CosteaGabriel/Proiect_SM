
// Proiect_SMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Proiect_SM.h"
#include "Proiect_SMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
int max_numbers_of_lines;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProiect_SMDlg dialog



CProiect_SMDlg::CProiect_SMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProiect_SMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProiect_SMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Magenta1);
}

BEGIN_MESSAGE_MAP(CProiect_SMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProiect_SMDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProiect_SMDlg::Add_Item_Col2)
END_MESSAGE_MAP()


// CProiect_SMDlg message handlers

BOOL CProiect_SMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	int InsertColumn(
		int nCol,
		const LVCOLUMN* pColumn
		);
	int InsertColumn(
		int nCol,
		LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT,
		int nWidth = 100,
		int nSubItem = -1
		);
	//Hello world

	if (Magenta1.InsertColumn(1, TEXT("Col1")) < 0)
		printf("error");
	if(Magenta1.InsertColumn(2, TEXT("Col2"))<0)
		printf("error");
	if(Magenta1.InsertColumn(3, TEXT("Col3"))<0)
		printf("error");

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProiect_SMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProiect_SMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProiect_SMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProiect_SMDlg::OnBnClickedButton1()
{
	int InsertItem(
		const LVITEM* pItem
		);
	int InsertItem(
		int nItem,
		LPCTSTR lpszItem
		);
	int InsertItem(
		int nItem,
		LPCTSTR lpszItem,
		int nImage
		);
	int InsertItem(
		UINT nMask,
		int nItem,
		LPCTSTR lpszItem,
		UINT nState,
		UINT nStateMask,
		int nImage,
		LPARAM lParam
		);

	BOOL SetItemText(
		int nItem,
		int nSubItem,
		LPCTSTR lpszText
		);
	

	if(Magenta1.InsertItem(1,0) < 0)
		printf("error");
	if (Magenta1.SetItemText(1, 0, TEXT("ELEMENT 1")) == 0)
		printf("error");

}


void CProiect_SMDlg::Add_Item_Col2()
{
	int InsertItem(
		const LVITEM* pItem
		);
	int InsertItem(
		int nItem,
		LPCTSTR lpszItem
		);
	int InsertItem(
		int nItem,
		LPCTSTR lpszItem,
		int nImage
		);
	int InsertItem(
		UINT nMask,
		int nItem,
		LPCTSTR lpszItem,
		UINT nState,
		UINT nStateMask,
		int nImage,
		LPARAM lParam
		);

	BOOL SetItemText(
		int nItem,
		int nSubItem,
		LPCTSTR lpszText
		);

	if (Magenta1.InsertItem(1, TEXT("EL1")) < 0)
		printf("error");
	if (Magenta1.SetItemText(1, 1, TEXT("ELEMENT 2")) == 0)
		printf("error");
	
}
