
#include "Stdafx.h"


CInternetSession mInterSession(L"Spider");

bool DownLoadImage(CString &strImgUrl)
{
	int idx = strImgUrl.ReverseFind('?');
	if (idx != -1) // 去掉图片后面的query
	{
		strImgUrl = strImgUrl.Left(idx);
	}

	int nLen = strImgUrl.GetLength();
	idx = strImgUrl.ReverseFind('/');
	idx = nLen-idx-1;
	CString imgName = strImgUrl.Right(idx);
	imgName = cfg->getFolder() + L"\\" + imgName;


	HRESULT ret;
	//for (int i = 0; i<2; i++)
	//{
		ret = ::URLDownloadToFile(NULL, strImgUrl, imgName, NULL,NULL);
		//if (!ret) break;
		if(ret) 
		{
			return false;
		}

		//Sleep(500);
	//}

	//if(ret) 
	//{
	//	return false;
	//}
	return true;
}

bool DownLoadPage(CString &strHtml,CString strPageUrl)
{
	DWORD ret = 0;
	CHttpFile *pFile = NULL;
	try
	{
		static CString strServer;
		static CString strObject;
		static INTERNET_PORT nPort;
		static DWORD dwServiceType;

		if(!AfxParseURL(strPageUrl,dwServiceType,strServer,strObject,nPort))
		{
			return false;
		}
		if(dwServiceType != INTERNET_SERVICE_HTTP)
		{
			return false;
		}

		pFile = (CHttpFile *)mInterSession.OpenURL(strPageUrl); // 用OpenRequest可能会在delete时出错；用DownloadUrlToFile怕会在写磁盘上花时间

		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		if (dwRet != HTTP_STATUS_OK) 
		{
			pFile->Close();
			if (pFile != NULL)
			{
				delete pFile;
			} 
			return false;
		}

		static char line[2000];
		while(pFile->ReadString((LPTSTR)line,1000)) // 注意此处1000是字符数！
		{
			strHtml += line;
		}
		pFile->Close();
	}
	catch (CInternetException* pEx)
	{
		pEx->Delete();
		return false;
	}
	if (pFile != NULL)
	{
		delete pFile;
	}
	return true;
}















