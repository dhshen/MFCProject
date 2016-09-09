
// SpiderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Spider.h"
#include "SpiderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Filter* filter = NULL;
Config* cfg = NULL;
URLList *ulist = NULL;
CSpiderDlg *sp = NULL;
bool ON_OFF = false;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSpiderDlg �Ի���




CSpiderDlg::CSpiderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpiderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_strHomePageUrl = _T("");
}

void CSpiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_strStatus);
	DDX_Control(pDX, IDC_STAT, m_strStat);
	DDX_Control(pDX, IDC_EDIT_DISPLAY, m_strDisplay);
	DDX_Control(pDX, IDC_EDITURL, m_strHomePageUrl);
}

BEGIN_MESSAGE_MAP(CSpiderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPT, &CSpiderDlg::OnBnClickedBtnOpt)
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CSpiderDlg::OnBnClickedBtnBegin)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CSpiderDlg::OnBnClickedBtnOutput)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CSpiderDlg::OnBnClickedBtnPause)
END_MESSAGE_MAP()


// CSpiderDlg ��Ϣ�������

BOOL CSpiderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	filter = new Filter();
	cfg = new Config();
	ulist = new URLList();
	sp = this;
	g_hMutex = CreateMutex( NULL,FALSE, NULL );
	s_hMutex = CreateMutex( NULL,FALSE, NULL );
	ON_OFF = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpiderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpiderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpiderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSpiderDlg::OnOK()
{
	return;
}

void CSpiderDlg::OnBnClickedBtnOpt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	optdlg.DoModal();
	InitOptValue();
}


void CSpiderDlg::InitOptValue()
{
	if(filter==NULL||cfg==NULL||ulist==NULL)
	{
		filter = new Filter();
		cfg = new Config();
		ulist = new URLList();
	}
	cfg->setPoxtFix(optdlg.m_strPostFix);
	cfg->setPageUrl(optdlg.m_strPageUrl);
	cfg->setImgUrl(optdlg.m_strImgUrl);
	cfg->setMaxImg(_ttoi(optdlg.m_strMaxImg));
	cfg->setIsOnlyHomePage(optdlg.m_isCurrent);
	cfg->setIsShow(optdlg.m_isShow);
	cfg->setTag(optdlg.m_strTag);
	cfg->setAttr(optdlg.m_strAttr);
	cfg->setTagKey(optdlg.m_strTagKey);
	cfg->setPageThread(_ttoi(optdlg.m_strThreadPage));
	cfg->setImgThread(_ttoi(optdlg.m_ThreadImg));
	cfg->setIsPageAll(optdlg.m_isParseAll);
}

void CSpiderDlg::OnBnClickedBtnBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_BEGIN);
	CString str;
	pBtn->GetWindowTextW(str);
	if(str==L"��ʼ")
	{
		m_strHomePageUrl.GetWindowTextW(str);
		if(str.IsEmpty())
		{
			AfxMessageBox(L"��������ڵ�ַ!");
			return;
		}
		if(str.Left(7)!=L"http://")
		{
			str = L"http://"+str;
		}
	
		CString st5 = str.Right(5);
		CString st4 = str.Right(4);
		if((st5!=L".html")&&(st4!=L".htm"))
		{
			if(str.Right(1)!= L"/")
			{
				str += L"/";
			}
		}

		m_strHomePageUrl.SetWindowTextW(str);

		if(filter==NULL||cfg==NULL||ulist==NULL)
		{
			filter = new Filter();
			cfg = new Config();
			ulist = new URLList();
		}

		cfg->setHomePageUrl(str);
		pBtn->SetWindowText(L"ֹͣ");
		ON_OFF = true;
		MainTask();
	}
	else if(str==L"ֹͣ"){
		ON_OFF = false;
		isPause = FALSE;
		pBtn->SetWindowText(L"����ֹͣ");
		SetStatusInfo(L"���ڵȺ��߳��˳�...");
		return;			
	}
	else{
		SetStatusInfo(L"����ֹͣ�����Ժ�...");
		return;
	}
}


void CSpiderDlg::OnBnClickedBtnOutput()
{
	// TODO: ��������
	CString strImgUrlForOut;
	if(strImgUrlForOut.IsEmpty())
	{
		AfxMessageBox(L"û�пɵ���������!");
		return;
	}
	CFileDialog* lpszOpenFile;
	TCHAR fileFilter[] = _T("TXT(*.txt)|*.txt||");
	CString szGetName;
	lpszOpenFile = new CFileDialog(FALSE,_T(""),_T(""),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,fileFilter,NULL);
	if (lpszOpenFile->DoModal()==IDOK)
	{		
		szGetName = lpszOpenFile->GetPathName();	
		delete lpszOpenFile;
	}
	else{
		return;
	}
	HANDLE hFile = CreateFile((LPCTSTR)szGetName,GENERIC_WRITE,0, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL );
	DWORD nWritten = 0;
	USES_CONVERSION;
	int nLen = strImgUrlForOut.GetLength();
	char* pFileName = T2A(strImgUrlForOut);
	WriteFile(hFile,pFileName,nLen,&nWritten,NULL);
	CloseHandle(hFile);

}


void CSpiderDlg::OnBnClickedBtnPause()
{
	// TODO: ��ͣ
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_PAUSE);
	CString str;
	pBtn->GetWindowTextW(str);
	if(str==L"��ͣ")
	{
		pBtn->SetWindowTextW(L"������ͣ");
		DealPause(TRUE);
	}
	else if(str==L"����"){
		DealPause(FALSE);
	}
	else{
		SetStatusInfo(L"������ͣ��");
		return;
	}
}


void CSpiderDlg::SetStatusInfo(CString infoStr)
{
	m_strStatus.SetWindowText(infoStr);
}

void CSpiderDlg::EchoInfo(CString infoStr)
{
	if(cfg->getIsShow())
	{
		return;
	}
	WaitForSingleObject(g_hMutex, INFINITE ); 
	
	echoStr += infoStr;
	echoStr += "\r\n";
	m_strDisplay.SetWindowText(echoStr);

	int nNow = m_strDisplay.GetFirstVisibleLine();
	int nLast = m_strDisplay.GetLineCount();
	m_strDisplay.LineScroll(nLast-nNow);

	int nMin,nMax;
	m_strDisplay.GetScrollRange(SB_VERT,&nMin,&nMax);
	m_strDisplay.SetScrollPos(SB_VERT,nMax);
	ReleaseMutex( g_hMutex );
}


void CSpiderDlg::DealStop()
{
	CString mStr;
	EchoInfo(L"\n* * * * * * * * * * * �� �� �� �� * * * * * * * * * * *");
	mStr.Format(L"\t\t������ҳ��:%d",ulist->getHaveDownPage());
	EchoInfo(mStr);
	mStr.Format(L"\t\t������ͼƬ:%d",ulist->getHaveDownImg());
	EchoInfo(mStr);
	mStr.Format(L"\t\tδ����ҳ��:%d",ulist->getWaitDownPage());
	EchoInfo(mStr);
	mStr.Format(L"\t\tδ����ͼƬ:%d",ulist->getWaitDownImg());
	EchoInfo(mStr);
	if((ulist->getWaitDownImg()) > 0)
	{
		EchoInfo(L"ͼƬ��δ��ȫ���أ���ʹ�õ���ͼƬ���ӵĹ��ܣ��������������Ƶ�Ѹ�����أ�");
	}
	SetStatusInfo(L"Ready");
	m_strStat.SetWindowText(L" ");

	delete(filter);
	filter=NULL;
	delete(cfg);
	cfg=NULL;
	delete(ulist);
	ulist=NULL;
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_BEGIN);
	pBtn->SetWindowText(L"��ʼ");
	filter = new Filter();
	cfg = new Config();
	ulist = new URLList();
}