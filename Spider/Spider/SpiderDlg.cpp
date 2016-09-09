
// SpiderDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSpiderDlg 对话框




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


// CSpiderDlg 消息处理程序

BOOL CSpiderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	filter = new Filter();
	cfg = new Config();
	ulist = new URLList();
	sp = this;
	g_hMutex = CreateMutex( NULL,FALSE, NULL );
	s_hMutex = CreateMutex( NULL,FALSE, NULL );
	ON_OFF = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSpiderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_BEGIN);
	CString str;
	pBtn->GetWindowTextW(str);
	if(str==L"开始")
	{
		m_strHomePageUrl.GetWindowTextW(str);
		if(str.IsEmpty())
		{
			AfxMessageBox(L"请输入入口地址!");
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
		pBtn->SetWindowText(L"停止");
		ON_OFF = true;
		MainTask();
	}
	else if(str==L"停止"){
		ON_OFF = false;
		isPause = FALSE;
		pBtn->SetWindowText(L"正在停止");
		SetStatusInfo(L"正在等候线程退出...");
		return;			
	}
	else{
		SetStatusInfo(L"正在停止，请稍后...");
		return;
	}
}


void CSpiderDlg::OnBnClickedBtnOutput()
{
	// TODO: 导出链接
	CString strImgUrlForOut;
	if(strImgUrlForOut.IsEmpty())
	{
		AfxMessageBox(L"没有可导出的内容!");
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
	// TODO: 暂停
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_PAUSE);
	CString str;
	pBtn->GetWindowTextW(str);
	if(str==L"暂停")
	{
		pBtn->SetWindowTextW(L"正在暂停");
		DealPause(TRUE);
	}
	else if(str==L"继续"){
		DealPause(FALSE);
	}
	else{
		SetStatusInfo(L"正在暂停中");
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
	EchoInfo(L"\n* * * * * * * * * * * 程 序 结 束 * * * * * * * * * * *");
	mStr.Format(L"\t\t共分析页面:%d",ulist->getHaveDownPage());
	EchoInfo(mStr);
	mStr.Format(L"\t\t共下载图片:%d",ulist->getHaveDownImg());
	EchoInfo(mStr);
	mStr.Format(L"\t\t未分析页面:%d",ulist->getWaitDownPage());
	EchoInfo(mStr);
	mStr.Format(L"\t\t未下载图片:%d",ulist->getWaitDownImg());
	EchoInfo(mStr);
	if((ulist->getWaitDownImg()) > 0)
	{
		EchoInfo(L"图片还未完全下载，可使用导出图片链接的功能，将链接批量复制到迅雷下载！");
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
	pBtn->SetWindowText(L"开始");
	filter = new Filter();
	cfg = new Config();
	ulist = new URLList();
}