#include "Stdafx.h"
#include "SpiderDlg.h"
#include "Config.h"

UINT DownHomePageProc( LPVOID pParam );
UINT DownPageProc( LPVOID pParam );
UINT DownImgProc( LPVOID pParam );
//UINT StatProc( LPVOID pParam );

int ThreadOver = 0;
BOOL isPause = FALSE;

void CSpiderDlg::MainTask()
{
	ThreadOver = 0;
	InitOptValue();

	CString str = cfg->getHomePageUrl().Right(cfg->getHomePageUrl().GetLength()-7);;
	int index = str.Find(L"/");
	str = str.Left(index);
	index = str.Find(L":");
	if(index != -1)
	{
		str = str.Left(index);
	}
	cfg->setFolder(str);
	::CreateDirectory((LPCTSTR)str,NULL); // ���ļ����Ѵ�����������
	EchoInfo(L"�ڵ�ǰĿ¼�´���Ŀ¼��"+str);
	str = L"http://"+str;
	cfg->setHostPath(str);
	::AfxBeginThread(DownHomePageProc,this,THREAD_PRIORITY_HIGHEST);
}

void CSpiderDlg::DealPause(BOOL type)
{
	if(type)
	{
		ON_OFF = false;
		isPause = TRUE;
	}
	else{
		ON_OFF = TRUE;
		isPause = FALSE;
		ThreadOver = 0;
		::AfxBeginThread(StatProc,NULL);
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_PAUSE);
		pBtn->SetWindowTextW(L"��ͣ");
	}
}

void CSpiderDlg::ThreadStat(bool zf)
{
	WaitForSingleObject(s_hMutex, INFINITE );
	if(zf)
	{
		ThreadOver++;
		SetStatusInfo(L"���߳�����");
	}
	else{
		ThreadOver--;
		SetStatusInfo(L"���߳��˳�");
		if(ThreadOver==0)
		{
			if(isPause)
			{
				CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_PAUSE);
				pBtn->SetWindowTextW(L"����");
				SetStatusInfo(L"��ͣ");
				EchoInfo(L"=============== �Ѿ���ͣ ==============");
				isPause = FALSE;
				ReleaseMutex( s_hMutex );
				return;
			}
			DealStop();
		}
	}
	CString strStatus;
	strStatus.Format(L"��ǰ�̣߳�%d",ThreadOver);
	SetStatusInfo(strStatus);
	ReleaseMutex( s_hMutex );
}

UINT DownHomePageProc(LPVOID pParam)
{
	int nPage = 0;
	int nImg = 0;
	sp->SetStatusInfo(L"���߳�����...");
	CString strHtml;
	sp->SetStatusInfo(L"������ҳ��...");
	if(!DownLoadPage(strHtml,cfg->getHomePageUrl()))
	{
		sp->EchoInfo(L"***��ҳ�� "+cfg->getHomePageUrl()+L"  ����ʧ��***");
		sp->SetStatusInfo(L"����ʧ�ܣ��˳���...");
		sp->DealStop();
		return 0;
	}
	sp->EchoInfo(L"�ɹ��������ҳ�棬��ʼ����...");

	ulist->queryPageUrLFromMark(cfg->getHomePageUrl());
	if(!cfg->getIsOnlyHomePage())
	{
		filter->GetPageUrlFromHTML(strHtml);
	}
	else{
		cfg->setPageThread(0);
	}
	filter->GetImgUrlFromHTML(strHtml);
	
	nPage = ulist->getWaitDownPage();
	nImg = ulist->getWaitDownImg();
	if((nPage==0)&&(nImg==0))
	{
		ON_OFF = false;
		sp->EchoInfo(L"�������ҳ��û�з������������ӻ�ͼƬ���ӣ����򼴽�������");
		return 0;
	}

	sp->EchoInfo(L"��ʼͳ��!");
	::AfxBeginThread(StatProc,NULL);
	return 0;
}


UINT StatProc( LPVOID pParam )
{
	sp->ThreadStat(true);
	int n = 0;	
	CString strStatus;
	//��ҳ���ء������߳�
	n = cfg->getPageThread();
	strStatus.Format(L"����%d��ҳ�������߳�!",n);
	sp->EchoInfo(strStatus);
	for( int i=0;i<n;i++)
	{
		::AfxBeginThread(DownPageProc,NULL);
	}
	//ͼƬ�����߳�
	n = cfg->getImgThread();
	strStatus.Format(L"����%d��ͼƬ�����߳�!",n);
	sp->EchoInfo(strStatus);
	for( int j=0;j<n;j++)
	{
		::AfxBeginThread(DownImgProc,NULL);
	}

	int nPage = 0;
	int nImg = 0;
	int nHaveImg = 0;
	
	while(1)
	{
		if((ON_OFF == false)||(isPause==TRUE))
		{
			sp->ThreadStat(false);
			return 0;
		}
		if(nHaveImg>=cfg->getMaxImg())
		{
			ON_OFF == false;
		}
		nPage = ulist->getWaitDownPage();
		nImg = ulist->getWaitDownImg();
		nHaveImg = ulist->getHaveDownImg();
		if((nPage==0)&&(nImg==0))
		{
			ON_OFF = false;
			sp->SetStatusInfo(L"������ɣ������˳�");
		}
		strStatus.Format(L"���ѡ�Page[%d]  Img[%d]  ��δ��Page[%d]  Img[%d]",ulist->getHaveDownPage(),
			nHaveImg,nPage,nImg);
		sp->m_strStat.SetWindowText(strStatus);
		Sleep(1000);
	}
}

UINT DownPageProc( LPVOID pParam )
{
	sp->ThreadStat(true);
	CString strHtml;
	CString strPageUrl;
	while(1)
	{
		if((ON_OFF == false)||(isPause==TRUE))
		{
			sp->ThreadStat(false);
			return 0;
		}
		strHtml.Empty();
		strPageUrl.Empty();
		if(ulist->getWaitDownPage()==0)
		{
			Sleep(4000);
			continue;
		}
		ulist->getOrAddWaitDownPageUrl(FALSE,strPageUrl);
		if(!DownLoadPage(strHtml,strPageUrl))
		{
			sp->EchoInfo(L"**��ҳ: "+strPageUrl+L" ʧ��!");
			continue;
		}
		sp->EchoInfo(L"��ҳ: "+strPageUrl);
		filter->GetPageUrlFromHTML(strHtml);
		filter->GetImgUrlFromHTML(strHtml);
	}
}

UINT DownImgProc( LPVOID pParam )
{
	sp->ThreadStat(true);
	CString strImgUrl;
	while(1)
	{
		if((ON_OFF == false)||(isPause==TRUE))
		{
			sp->ThreadStat(false);
			return 0;
		}
		if(ulist->getWaitDownImg()==0)
		{
			Sleep(5000);
			continue;
		}
		ulist->getOrAddWaitDownImgUrl(FALSE,strImgUrl);
		if(!DownLoadImage(strImgUrl))
		{
			sp->EchoInfo(L"**ͼƬ: "+strImgUrl+L" ʧ��");
			continue;
		}
		sp->EchoInfo(L"ͼƬ: "+strImgUrl);
	}
}