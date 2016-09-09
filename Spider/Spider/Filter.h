#pragma once
#include "Config.h"
#include "URLList.h"
class Filter
{
public:
	Filter(void);
	~Filter(void);

public:
	//Config *cfg;		//������Ϣ
	//URLList *ulist;		//url����

	bool GetTagFromHTML(CString &strHtml, CString strTagName, int &nBeginPos, CString &strTagContent);

	bool GetAttrFromTag(CString &strTagContent, CString strAttName, CString &strAttContent);

	bool CheckImgUrl(CString &strURL);

	void GetImgUrlFromHTML(CString strHtml);

	bool CheckPageUrl(CString &strURL);

	void GetPageUrlFromHTML(CString &strHtml);

	void GetImgUrlFromHTTP(CString &strHtml);

	 //��·��ת���ɾ���·��
	void TurnToAbsolutePath(CString &path);

};

