
// SpiderDlg.h : ͷ�ļ�
//

#pragma once
#include "OptDlg.h"
#include "afxwin.h"

// CSpiderDlg �Ի���
class CSpiderDlg : public CDialogEx
{
// ����
public:
	CSpiderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPIDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	CString echoStr; //������������������Ϣ
	HANDLE g_hMutex;	//���ڿ�������Ļ�����
	HANDLE s_hMutex;	//���ڿ��ƽ����˳�״̬�Ļ�����
};
