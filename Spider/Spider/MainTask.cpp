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
	::CreateDirectory((LPCTSTR)str,NULL); // 若文件夹已存在则不作处理
	EchoInfo(L"在当前目录下创建目录："+str);
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
		pBtn->SetWindowTextW(L"暂停");
	}
}

void CSpiderDlg::ThreadStat(bool zf)
{
	WaitForSingleObject(s_hMutex, INFINITE );
	if(zf)
	{
		ThreadOver++;
		SetStatusInfo(L"有线程启动");
	}
	else{
		ThreadOver--;
		SetStatusInfo(L"有线程退出");
		if(ThreadOver==0)
		{
			if(isPause)
			{
				CButton *pBtn = (CButton *)GetDlgItem(IDC_BTN_PAUSE);
				pBtn->SetWindowTextW(L"继续");
				SetStatusInfo(L"暂停");
				EchoInfo(L"=============== 已经暂停 ==============");
				isPause = FALSE;
				ReleaseMutex( s_hMutex );
				return;
			}
			DealStop();
		}
	}
	CString strStatus;
	strStatus.Format(L"当前线程：%d",ThreadOver);
	SetStatusInfo(strStatus);
	ReleaseMutex( s_hMutex );
}

UINT DownHomePageProc(LPVOID pParam)
{
	int nPage = 0;
	int nImg = 0;
	sp->SetStatusInfo(L"主线程启动...");
	CString strHtml;
	sp->SetStatusInfo(L"下载主页中...");
	if(!DownLoadPage(strHtml,cfg->getHomePageUrl()))
	{
		sp->EchoInfo(L"***网页： "+cfg->getHomePageUrl()+L"  下载失败***");
		sp->SetStatusInfo(L"下载失败，退出中...");
		sp->DealStop();
		return 0;
	}
	sp->EchoInfo(L"成功下载入口页面，开始分析...");

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
		sp->EchoInfo(L"入口链接页面没有符合条件的链接或图片链接，程序即将结束！");
		return 0;
	}

	sp->EchoInfo(L"开始统计!");
	::AfxBeginThread(StatProc,NULL);
	return 0;
}


UINT StatProc( LPVOID pParam )
{
	sp->ThreadStat(true);
	int n = 0;	
	CString strStatus;
	//网页下载、分析线程
	n = cfg->getPageThread();
	strStatus.Format(L"启动%d个页面下载线程!",n);
	sp->EchoInfo(strStatus);
	for( int i=0;i<n;i++)
	{
		::AfxBeginThread(DownPageProc,NULL);
	}
	//图片下载线程
	n = cfg->getImgThread();
	strStatus.Format(L"启动%d个图片下载线程!",n);
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
			sp->SetStatusInfo(L"下载完成，正在退出");
		}
		strStatus.Format(L"【已】Page[%d]  Img[%d]  【未】Page[%d]  Img[%d]",ulist->getHaveDownPage(),
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
			sp->EchoInfo(L"**网页: "+strPageUrl+L" 失败!");
			continue;
		}
		sp->EchoInfo(L"网页: "+strPageUrl);
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
			sp->EchoInfo(L"**图片: "+strImgUrl+L" 失败");
			continue;
		}
		sp->EchoInfo(L"图片: "+strImgUrl);
	}
}