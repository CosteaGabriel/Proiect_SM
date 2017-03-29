
// Proiect_SMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Proiect_SM.h"
#include "Proiect_SMDlg.h"
#include "afxdialogex.h"

#include <Psapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VECTOR_SIZE 500 //numarul total de numere generate
#define MAX_VAL 10000   //valoarea maxima pe care o poate lua un numar

// CAboutDlg dialog used for App About
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
	ON_BN_CLICKED(IDC_BUTTON1, &CProiect_SMDlg::Process_Info)
	ON_BN_CLICKED(IDC_BUTTON2, &CProiect_SMDlg::Compare)
	ON_BN_CLICKED(IDC_BUTTON3, &CProiect_SMDlg::CPUID_Button)
	ON_BN_CLICKED(IDC_BUTTON4, &CProiect_SMDlg::RTDSC_Button)
END_MESSAGE_MAP()


// CProiect_SMDlg message handlers

BOOL CProiect_SMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//Inserare coloane
	int InsertColumn(
		int nCol,
		const LVCOLUMN* pColumn
		);
	int InsertColumn(
		int nCol,
		LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_CENTER,
		int nWidth = 1000,
		int nSubItem = -1
		);

	BOOL SetColumnWidth(
		int nCol,
		int cx
		);
	//inseram 3 coloana in List Control
	Magenta1.InsertColumn(1, TEXT("Proprietate"));
	Magenta1.InsertColumn(2, TEXT("Valoarea"));
	Magenta1.InsertColumn(3, TEXT("Unitatea de masura"));

	//setam dimensiunea coloanei la 150 pixeli
	Magenta1.SetColumnWidth(0, 200);
	Magenta1.SetColumnWidth(1, 150);
	Magenta1.SetColumnWidth(2, 150);


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

int *input_array = new int[VECTOR_SIZE]; //vectorul ce va fi folosit de algoritmul de sortare
int *bkup_numbers = new int[VECTOR_SIZE]; //vector de rezerva folosit pentru reinitializarea  
void CProiect_SMDlg::generateNumbers(int length) {
	srand(time(NULL));
	int i = 0;
	for (i = 0; i < length; i++) {
		input_array[i] = (rand() % MAX_VAL);
		bkup_numbers[i] = input_array[i];
	}
}
void CProiect_SMDlg::initializeNumbers() {
	for (int i = 0; i < VECTOR_SIZE; i++)
		input_array[i] = bkup_numbers[i];
}
//shell sort
void CProiect_SMDlg::shellSort(int data[], int lenD)
{
	int inc = lenD / 2;
	while (inc>0){
		for (int i = inc; i<lenD; i++){
			int tmp = data[i];
			int j = i;
			while (j >= inc && data[j - inc]>tmp){
				data[j] = data[j - inc];
				j = j - inc;
			}
			data[j] = tmp;
		}
		inc = (inc / 2);
	}
}
//bubble sort
void CProiect_SMDlg::bubbleSort(int data[], int lenD)
{
	int tmp = 0;
	for (int i = 0; i<lenD; i++){
		for (int j = (lenD - 1); j >= (i + 1); j--){
			if (data[j]<data[j - 1]){
				tmp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = tmp;
			}
		}
		/*CString txt;
		txt.Format(TEXT("%d"), data[i]);
		c_list.InsertItem(nItem++, txt);*/
	}
}
//insertion sort
void CProiect_SMDlg::insertionSort(int data[], int lenD)
{
	int key = 0;
	int i = 0;
	for (int j = 1; j<lenD; j++){
		key = data[j];
		i = j - 1;
		while (i >= 0 && data[i]>key){
			data[i + 1] = data[i];
			i = i - 1;
			data[i + 1] = key;
		}
	}
}

void CProiect_SMDlg::Process_Info()
{
	SYSTEM_INFO SysInfo;
	MEMORYSTATUSEX MemoryInfo;
	_PERFORMANCE_INFORMATION PerformanceInfo;			

	MemoryInfo.dwLength = sizeof(MemoryInfo);

	wchar_t buffer[500];								//variabila folosita pentru stocarea si afisarea informatiei

	Magenta1.DeleteAllItems();							//stergem toate elementele din ListControl inainte sa le afisam pe cele noi


	int InsertItem(										//functie pentru inserarea unei linii
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

	BOOL SetItemText(					//functie pt setarea textului unei linii
		int nItem,
		int nSubItem,
		LPCTSTR lpszText
		);


	LVCOLUMN aux_col; //variabila ce va contine datele coloanei
	int column_index = 0; //column_index reprezinta indexul coloanei care va fi
	//modificata
	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in


	aux_col.pszText = TEXT("Proprietate"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("Valoare"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("Unitatea de masura"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	Magenta1.DeleteAllItems();

	//functii pentru aflarea informatiei HW-ului
	GetPerformanceInfo(&PerformanceInfo, sizeof(PerformanceInfo));
	GetSystemInfo(&SysInfo); 
	GlobalMemoryStatusEx(&MemoryInfo);

	//Afisam page size
	swprintf_s(buffer, 500, L"%d",  SysInfo.dwPageSize);

	Magenta1.InsertItem(0, 0);
	Magenta1.SetItemText(0, 0, TEXT("Dim pag memorie"));
	Magenta1.SetItemText(0, 1, buffer);
	Magenta1.SetItemText(0, 2, TEXT("bytes"));

	//Afisam minim virtual memory
	swprintf_s(buffer, 500, L"%lu", SysInfo.lpMinimumApplicationAddress);

	Magenta1.InsertItem(1, 0);
	Magenta1.SetItemText(1, 0, TEXT("Adrs. minima de mem virt"));
	Magenta1.SetItemText(1, 1, buffer);
	Magenta1.SetItemText(1, 2, TEXT("Adress"));
	
	//Afisam maxim virtual memory
	swprintf_s(buffer, 500, L"%lu", SysInfo.lpMaximumApplicationAddress);

	Magenta1.InsertItem(2, 0);
	Magenta1.SetItemText(2, 0, TEXT("Adrs. maxima de mem virt"));
	Magenta1.SetItemText(2, 1, buffer);
	Magenta1.SetItemText(2, 2, TEXT("Adress"));

	//Afisam total memory space
	swprintf_s(buffer, 500, L"%lu", MemoryInfo.ullTotalPhys);

	Magenta1.InsertItem(3, 0);

	Magenta1.SetItemText(3, 0, TEXT("Total memory"));
	Magenta1.SetItemText(3, 1, buffer);
	Magenta1.SetItemText(3, 2, TEXT("bytes"));

	//Afisam toal availlable physical memory
	swprintf_s(buffer, 500, L"%lu", MemoryInfo.ullAvailPhys);

	Magenta1.InsertItem(4, 0);

	Magenta1.SetItemText(4, 0, TEXT("Total avl. mem"));
	Magenta1.SetItemText(4, 1, buffer);;
	Magenta1.SetItemText(4, 2, TEXT("bytes"));
	
	//Total SO memory
	swprintf_s(buffer, 500, L"%u", PerformanceInfo.KernelTotal);

	Magenta1.InsertItem(5, 0);
	Magenta1.SetItemText(5, 0, TEXT("Total SO mem"));
	Magenta1.SetItemText(5, 1, buffer);
	Magenta1.SetItemText(5, 2, TEXT("pages"));
	
	//Total virtual memory
	swprintf_s(buffer, 500, L"%u", MemoryInfo.ullTotalVirtual);
	
	Magenta1.InsertItem(6, 0);
	Magenta1.SetItemText(6, 0, TEXT("Total virtual mem"));
	Magenta1.SetItemText(6, 1, buffer);
	Magenta1.SetItemText(6, 2, TEXT("bytes"));


	//Available virtual memory
	swprintf_s(buffer, 500, L"%u", MemoryInfo.ullAvailVirtual);

	Magenta1.InsertItem(7, 0);
	Magenta1.SetItemText(7, 0, TEXT("Available virtual mem"));
	Magenta1.SetItemText(7, 1, buffer);
	Magenta1.SetItemText(7, 2, TEXT("bytes"));

	//Memor load
	swprintf_s(buffer, 500, L"%d", MemoryInfo.dwMemoryLoad);

	Magenta1.InsertItem(8, 0);
	Magenta1.SetItemText(8, 0, TEXT("Memory load"));
	Magenta1.SetItemText(8, 1, buffer);
	Magenta1.SetItemText(8, 2, TEXT("%"));
}

void CProiect_SMDlg::Compare()
{
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	CString txt;

	QueryPerformanceCounter(&Frequency);

	int InsertItem(										//functie pentru inserarea unei linii
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

	BOOL SetItemText(					//functie pt setarea textului unei linii
		int nItem,
		int nSubItem,
		LPCTSTR lpszText
		);



	LVCOLUMN aux_col; //variabila ce va contine datele coloanei
	int column_index = 0; //column_index reprezinta indexul coloanei care va fi
	//modificata
	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in



	aux_col.pszText = TEXT("Alrgoritmu de sortare"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("Diferenta"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("Timp"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	Magenta1.DeleteAllItems();										



	generateNumbers(VECTOR_SIZE);

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
	bubbleSort(input_array, VECTOR_SIZE);
	QueryPerformanceCounter(&EndingTime);

	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);

	Magenta1.InsertItem(0, 0);
	Magenta1.SetItemText(0, 0, TEXT("Bubble Sort"));
	Magenta1.SetItemText(0, 1, txt);

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.SetItemText(0, 2, txt);


	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
	insertionSort(input_array, VECTOR_SIZE);
	QueryPerformanceCounter(&EndingTime);

	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);

	Magenta1.InsertItem(1, 0);
	Magenta1.SetItemText(1, 0, TEXT("Insertion Sort"));
	Magenta1.SetItemText(1, 1, txt);

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.SetItemText(1, 2, txt);


	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
	shellSort(input_array, VECTOR_SIZE);
	QueryPerformanceCounter(&EndingTime);

	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;



	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);

	Magenta1.InsertItem(2, 0);
	Magenta1.SetItemText(2, 0, TEXT("Shell Sort"));
	Magenta1.SetItemText(2, 1, txt);

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.SetItemText(2, 2, txt);
}


void CProiect_SMDlg::CPUID_Button()
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


	LVCOLUMN aux_col; //variabila ce va contine datele coloanei
	int column_index = 0; //column_index reprezinta indexul coloanei care va fi
	//modificata
	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in



	aux_col.pszText = TEXT("A"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("D"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("T"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	Magenta1.DeleteAllItems();										//variabila aux_col


	wchar_t buffer[20];
	int vendor_id, description, brand_id, ft_flags, nr_processors;

	_asm{
		mov eax, 0
			cpuid
			mov vendor_id, ebx

			mov eax, 1
			cpuid
			mov description, eax
			mov brand_id, ebx
			mov ft_flags, edx

			mov eax, 0Ah
			cpuid
			mov nr_processors, eax
	}

	//swprintf_s(buffer, 20, L"%d", vendor_id);
	switch (vendor_id  & 0x3000)
	{
		case 0:
			Magenta1.InsertItem(0, 0);
			Magenta1.SetItemText(0, 0, TEXT("Processor Type"));
			Magenta1.SetItemText(0, 1, TEXT("Original OEM rocessor"));
			break;
		case 0x1000:
			Magenta1.InsertItem(0, 0);
			Magenta1.SetItemText(0, 0, TEXT("Processor Type"));
			Magenta1.SetItemText(0, 1, TEXT("Overdrive Processor"));
			break;
		case 0x2000:
			Magenta1.InsertItem(0, 0);
			Magenta1.SetItemText(0, 0, TEXT("Processor Type"));
			Magenta1.SetItemText(0, 1, TEXT("Dual Processor"));
			break;
		default:
			break;
	}




	
	/*
	Magenta1.InsertItem(2, 0);
	Magenta1.SetItemText(2, 0, TEXT("Shell Sort"));
	Magenta1.SetItemText(2, 1, txt);
	*/
	
	swprintf_s(buffer, 20, L"%d", description);

	Magenta1.InsertItem(1, 0);
	Magenta1.SetItemText(1, 0, TEXT("Vendor ID"));
	Magenta1.SetItemText(1, 0, buffer);



	swprintf_s(buffer, 20, L"%d", brand_id);
	if (Magenta1.InsertItem(2, 0) < 0)
		printf("error");

	if (Magenta1.SetItemText(2, 0, buffer) == 0)
		printf("error");



	swprintf_s(buffer, 20, L"%d", ft_flags);
	if (Magenta1.InsertItem(3, 0) < 0)
		printf("error");

	if (Magenta1.SetItemText(3, 0, buffer) == 0)
		printf("error");


	swprintf_s(buffer, 20, L"%d", nr_processors);
	if (Magenta1.InsertItem(4, 0) < 0)
		printf("error");

	if (Magenta1.SetItemText(4, 0, buffer) == 0)
		printf("error");
		
}


void CProiect_SMDlg::RTDSC_Button()
{

	wchar_t buffer[20];
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	CString txt;


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




	LVCOLUMN aux_col; //variabila ce va contine datele coloanei
	int column_index = 0; //column_index reprezinta indexul coloanei care va fi
	//modificata
	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in


	aux_col.pszText = TEXT("Proprietate"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT("Valoare"); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	column_index++;

	Magenta1.GetColumn(column_index, &aux_col); //se obtin datele coloanei cu indexul
	//column_index si se stocheaza in
	//variabila aux_col
	aux_col.pszText = TEXT(""); //se modifica titlul coloanei
	Magenta1.SetColumn(column_index, &aux_col); //se seteaza noile date ale coloanei

	Magenta1.DeleteAllItems();


	unsigned long ticks_start = 0, ticks_stop = 0, freq = 0;

	_asm{
		rdtsc
			mov ticks_start, edx
			shl ticks_start, 32
			xor ticks_start, eax
	}

	Sleep(1000);
	_asm{
		rdtsc
			mov ticks_stop, edx
			shl ticks_stop, 32
			xor ticks_stop, eax
	}

	freq = (ticks_stop - ticks_start) / 1000000;

	swprintf_s(buffer, 20, L"%d", freq);

	Magenta1.InsertItem(0, 0);
	Magenta1.SetItemText(0, 0, TEXT("Frecventa curenta a procesorului"));
	Magenta1.SetItemText(0, 1, buffer);

	SetThreadAffinityMask(GetCurrentThread(), 1 << 1);

	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.InsertItem(1, 0);
	Magenta1.SetItemText(1, 0, TEXT("BELOW NORMAL PRIORITY CLASS"));
	Magenta1.SetItemText(1, 1, txt);

	

	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.InsertItem(2, 0);
	Magenta1.SetItemText(2, 0, TEXT("NORMAL PRIORITY CLASS"));
	Magenta1.SetItemText(2, 1, txt);

	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);

	Magenta1.InsertItem(3, 0);
	Magenta1.SetItemText(3, 0, TEXT("HIGH PRIORITY CLASS"));
	Magenta1.SetItemText(3, 1, txt);


//#############################################################################################################################//


	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.InsertItem(4, 0);
	Magenta1.SetItemText(4, 0, TEXT("THREAD_PRIORITY_LOWEST"));
	Magenta1.SetItemText(4, 1, txt);



	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.InsertItem(5, 0);
	Magenta1.SetItemText(5, 0, TEXT("THREAD_PRIORITY_NORMAL"));
	Magenta1.SetItemText(5, 1, txt);

	
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	txt.Format(TEXT("%lld"), ElapsedMicroseconds.QuadPart);
	Magenta1.InsertItem(6, 0);
	Magenta1.SetItemText(6, 0, TEXT("THREAD_PRIORITY_HIGHEST"));
	Magenta1.SetItemText(6, 1, txt);
}
