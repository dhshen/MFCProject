#pragma once
#include "afxwin.h"
#include "Resource.h"

// COptDlg �Ի���

class COptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptDlg)

public:
	COptDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptDlg();

// �Ի�������
	enum { IDD = IDD_DLG_OPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOK();

	CString m_strPostFix;
	CString m_strPageUrl;
	CString m_strImgUrl;
	CString m_strMaxImg;
	BOOL m_isCurrent;
	BOOL m_isShow;
	CString m_strTag;
	CString m_strAttr;
	CString m_strTagKey;
	CString m_strThreadPage;
	CString m_ThreadImg;
	BOOL m_isParseAll;
	afx_msg void OnBnClickedBtnok();
	afx_msg void OnBnClickedBtncancel();
};
