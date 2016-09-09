#pragma once
class Config
{
public:
	Config(void);
	~Config(void);

private:
	CString strHomePageUrl;
	CString strPoxtFix;
	CString strPageUrl;
	CString strImgUrl;
	int nMaxImg;
	BOOL isOnlyHomePage;
	BOOL isShow;
	CString strTag;
	CString strAttr;
	CString strTagKey;
	int nPageThread;
	int nImgThread;
	BOOL isParseALL;
	CString folder;

	CString hostPath;
public:
	CString getHomePageUrl();
	void setHomePageUrl(CString& str);

	CString getPoxtFix();
	void setPoxtFix(CString str);

	CString getPageUrl();
	void setPageUrl(CString str);

	CString getImgUrl();
	void setImgUrl(CString str);

	int getMaxImg();
	void setMaxImg(int n);

	BOOL getIsOnlyHomePage();
	void setIsOnlyHomePage(BOOL ok);

	BOOL getIsShow();
	void setIsShow(BOOL ok);

	CString getTag();
	void setTag(CString str);

	CString getAttr();
	void setAttr(CString str);

	CString getTagKey();
	void setTagKey(CString str);

	int getPageThread();
	void setPageThread(int n);

	int getImgThread();
	void setImgThread(int n);

	BOOL getIsParseAll();
	void setIsPageAll(BOOL ok);

	CString getFolder();
	void setFolder(CString& str);

	CString getHostPath();
	void setHostPath(CString& str);
};

