#include "StdAfx.h"
#include "Config.h"


Config::Config(void)
{
	strHomePageUrl.Empty();
	strPoxtFix.Empty();
	strPageUrl.Empty();
	strImgUrl.Empty();
	nMaxImg = 0;
	isOnlyHomePage = FALSE;
	isShow = FALSE;
	strTag.Empty();
	strAttr.Empty();
	strTagKey.Empty();
	nPageThread = 0;
	nImgThread = 0;
	isParseALL = FALSE;
	folder.Empty();

	hostPath.Empty();
}


Config::~Config(void)
{
}


CString Config::getHomePageUrl()
{
	return this->strHomePageUrl;
}
void Config::setHomePageUrl(CString& str)
{
	this->strHomePageUrl = str;
}

CString Config::getPoxtFix()
{
	return this->strPoxtFix;
}
void Config::setPoxtFix(CString str)
{
	this->strPoxtFix = str;
}

CString Config::getPageUrl()
{
	return this->strPageUrl;
}
void Config::setPageUrl(CString str)
{
	this->strPageUrl = str;
}

CString Config::getImgUrl()
{
	return this->strImgUrl;
}
void Config::setImgUrl(CString str)
{
	this->strImgUrl = str;
}

int Config::getMaxImg()
{
	return this->nMaxImg;
}
void Config::setMaxImg(int n)
{
	this->nMaxImg = n;
}

BOOL Config::getIsOnlyHomePage()
{
	return this->isOnlyHomePage;
}
void Config::setIsOnlyHomePage(BOOL ok)
{
	this->isOnlyHomePage = ok;
}

BOOL Config::getIsShow()
{
	return this->isShow;
}
void Config::setIsShow(BOOL ok)
{
	this->isShow = ok;
}

CString Config::getTag()
{
	return this->strTag;
}
void Config::setTag(CString str)
{
	this->strTag = str;
}

CString Config::getAttr()
{
	return this->strAttr;
}
void Config::setAttr(CString str)
{
	this->strAttr = str;
}

CString Config::getTagKey()
{
	return this->strTagKey;
}
void Config::setTagKey(CString str)
{
	this->strTagKey = str;
}

int Config::getPageThread()
{
	return this->nPageThread;
}
void Config::setPageThread(int n)
{
	this->nPageThread = n;
}

int Config::getImgThread()
{
	return this->nImgThread;
}
void Config::setImgThread(int n)
{
	this->nImgThread = n;
}

BOOL Config::getIsParseAll()
{
	return this->isParseALL;
}
void Config::setIsPageAll(BOOL ok)
{
	this->isParseALL = ok;
}

CString Config::getFolder()
{
	return this->folder;
}
void Config::setFolder(CString& str)
{
	this->folder = str;
}

CString Config::getHostPath()
{
	return this->hostPath;
}
void Config::setHostPath(CString& str)
{
	this->hostPath = str;
}