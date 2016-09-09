#pragma once
#include "Config.h"
#include "URLList.h"
class Filter
{
public:
	Filter(void);
	~Filter(void);

public:
	//Config *cfg;		//配置信息
	//URLList *ulist;		//url队列

	bool GetTagFromHTML(CString &strHtml, CString strTagName, int &nBeginPos, CString &strTagContent);

	bool GetAttrFromTag(CString &strTagContent, CString strAttName, CString &strAttContent);

	bool CheckImgUrl(CString &strURL);

	void GetImgUrlFromHTML(CString strHtml);

	bool CheckPageUrl(CString &strURL);

	void GetPageUrlFromHTML(CString &strHtml);

	void GetImgUrlFromHTTP(CString &strHtml);

	 //将路径转换成绝对路径
	void TurnToAbsolutePath(CString &path);

};

