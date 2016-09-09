
// SpiderDlg.h : 头文件
//

#pragma once
#include "OptDlg.h"
#include "afxwin.h"

// CSpiderDlg 对话框
class CSpiderDlg : public CDialogEx
{
// 构造
public:
	CSpiderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPIDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedBtnOpt();
	afx_msg void OnBnClickedBtnBegin();
	afx_msg void OnBnClickedBtnOutput();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnOK();

	void InitOptValue();
	void MainTask();
	void SetStatusInfo(CString infoStr);
	void ThreadStat(bool zf);
	void EchoInfo(CString infoStr);
	void DealStop();
	void DealPause(BOOL type);

	COptDlg optdlg;
	CEdit m_strHomePageUrl;
	CEdit m_strStatus;
	CEdit m_strStat;
	CEdit m_strDisplay;

	CString echoStr; //输出到主界面的下载信息
	HANDLE g_hMutex;	//用于控制输出的互斥量
	HANDLE s_hMutex;	//用于控制进程退出状态的互斥量
};
