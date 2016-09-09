#pragma once

#include "Util.h"

typedef CList<CString,CString> STRLST;

class URLList
{
public:
	URLList(void);
	~URLList(void);

private:
	STRLST s_PageUrlMark;
	STRLST s_ImgUrlMark;
	STRLST s_waitDownImgUrl;
	STRLST s_waitDownPageUrl;

	int HaveDownPage;
	int HaveDownImg;
	int WaitDownPage;
	int WaitDownImg;
private:
	HANDLE a_hMutex;
	HANDLE b_hMutex;
	HANDLE c_hMutex;
	HANDLE d_hMutex;
	HANDLE e_hMutex;
public:
	BOOL queryPageUrLFromMark(CString &str);
	BOOL queryImgUrLFromMark(CString &str);

	//void addWaitDownImgUrl(CString &str);
	//void getImgUrlFromWaitDown(CString &str);
	void getOrAddWaitDownImgUrl(BOOL type,CString &str);

	//void addWaitDownPageUrl(CString &str);
	//void getPageUrlFromWaitDown(CString &str);
	void getOrAddWaitDownPageUrl(BOOL type,CString &str);

	int getHaveDownPage();
	int getHaveDownImg();
	int getWaitDownPage();
	int getWaitDownImg();
};

