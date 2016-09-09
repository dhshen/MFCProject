// OptDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Spider.h"
#include "OptDlg.h"
#include "afxdialogex.h"


// COptDlg 对话框

IMPLEMENT_DYNAMIC(COptDlg, CDialogEx)

COptDlg::COptDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COptDlg::IDD, pParent)
	, m_strPostFix(_T("jpg"))
	, m_strPageUrl(_T(""))
	, m_strImgUrl(_T(""))
	, m_strMaxImg(_T(""))
	, m_isCurrent(FALSE)
	, m_isShow(FALSE)
	, m_strTag(_T("img"))
	, m_strAttr(_T("src"))
	, m_strTagKey(_T(""))
	, m_strThreadPage(_T("3"))
	, m_ThreadImg(_T("3"))
	, m_isParseAll(FALSE)
{

}

COptDlg::~COptDlg()
{
}

void COptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, OPT_POSTFIX, m_strPostFix);
	//  DDX_Control(pDX, OPT_PAGEURL_KEY, m_strPageUrl);
	//  DDX_Control(pDX, IDC_IMGURL_KEY, m_strImgUrl);
	//  DDX_Control(pDX, OPT_MAXIMG, m_strMaxImg);
	//  DDX_Control(pDX, OPT_CURPAGE, m_isCurrent);
	//  DDX_Control(pDX, IDC_ISDISPLAY, m_isShow);
	//  DDX_Control(pDX, OPT_POS_TAG, m_strTag);
	//  DDX_Control(pDX, OPT_POS_ATTR, m_strAttr);
	//  DDX_Control(pDX, OPT_POS_TAGKEY, m_strTagKey);
	//  DDX_Control(pDX, OPT_THPAGESUM, m_strThreadPage);
	//  DDX_Control(pDX, IDC_THIMGSUM, m_ThreadImg);
	//  DDX_Control(pDX, OPT_ISALL, m_isParseAll);
	DDX_Text(pDX, OPT_POSTFIX, m_strPostFix);
	DDX_Text(pDX, OPT_PAGEURL_KEY, m_strPageUrl);
	DDX_Text(pDX, IDC_IMGURL_KEY, m_strImgUrl);
	DDX_Text(pDX, OPT_MAXIMG, m_strMaxImg);
	DDX_Check(pDX, OPT_CURPAGE, m_isCurrent);
	DDX_Check(pDX, IDC_ISDISPLAY, m_isShow);
	DDX_Text(pDX, OPT_POS_TAG, m_strTag);
	DDX_Text(pDX, OPT_POS_ATTR, m_strAttr);
	DDX_Text(pDX, OPT_POS_TAGKEY, m_strTagKey);
	DDX_Text(pDX, OPT_THPAGESUM, m_strThreadPage);
	DDX_Text(pDX, IDC_THIMGSUM, m_ThreadImg);
	DDX_Check(pDX, OPT_ISALL, m_isParseAll);
}


BEGIN_MESSAGE_MAP(COptDlg, CDialogEx)
	ON_BN_CLICKED(OPT_BTNOK, &COptDlg::OnBnClickedBtnok)
	ON_BN_CLICKED(OPT_BTNCANCEL, &COptDlg::OnBnClickedBtncancel)
END_MESSAGE_MAP()


// COptDlg 消息处理程序

void COptDlg::OnOK()
{
	return;
}

void COptDlg::OnBnClickedBtnok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialog::OnOK();
}


void COptDlg::OnBnClickedBtncancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
