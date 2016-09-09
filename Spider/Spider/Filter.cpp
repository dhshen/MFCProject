#include "StdAfx.h"
#include "Filter.h"


Filter::Filter(void)
{

}


Filter::~Filter(void)
{
}


bool Filter::GetTagFromHTML(CString &strHtml, CString strTagName, int &nBeginPos, CString &strTagContent)
{
	if(strHtml.IsEmpty()||strTagName.IsEmpty())
	{
		return false;
	}
	int index1 = strHtml.Find(L"<"+strTagName.MakeUpper()+L" ",nBeginPos);
	int index2 = strHtml.Find(L"<"+strTagName.MakeLower()+L" ",nBeginPos);

	if((index1>-1)&&(index2>-1))
	{
		index1 = __min(index1,index2);
	}
	else{
		index1 = __max(index1,index2);
		if(index1 == -1)
		{
			return false;
		}
	}

	index2 = strHtml.Find(L">",index1);
	if(index1 == -1)
	{
		return false;
	}
	strTagContent = strHtml.Mid(index1+1,index2-index1-1);

	if(strTagContent.Right(1) == L"/")
	{
		strTagContent.Left(strTagContent.GetLength()-1);
	}
	nBeginPos = index2+1;
	return true;
}

bool Filter::GetAttrFromTag(CString &strTagContent, CString strAttName, CString &strAttContent)
{
	int index1 = strTagContent.Find(L" "+strAttName.MakeUpper()+L"=");
	int index2 = strTagContent.Find(L" "+strAttName.MakeLower()+L"=");
	if((index1>-1)&&(index2>-1))
	{
		index1 = __min(index1,index2);
	}
	else{
		index1 = __max(index1,index2);
		if(index1 == -1)
		{
			return false;
		}
	}

	index2 = strTagContent.Find(L" ",index1+2);
	if(index2 == -1)
	{
		index2 = strTagContent.GetLength();
	}
	index1 += strAttName.GetLength()+2;
	strAttContent = strTagContent.Mid(index1,index2-index1);
	if((strAttContent.Left(1) == L"\"") || (strAttContent.Left(1) == L"'"))
	{
		strAttContent = strAttContent.Right(strAttContent.GetLength()-1);
	}
	while(strAttContent.Right(1) == L"\"" || strAttContent.Right(1) == L"'" || strAttContent.Right(1) == L"\n") 
	{
		strAttContent = strAttContent.Left(strAttContent.GetLength()-1);
	}	
	return true;
}

bool Filter::CheckImgUrl(CString &strURL)
{
	strURL.Remove('<');
	strURL.Remove('>');

	if(!(cfg->getPoxtFix().IsEmpty()))
	{
		int nLen = cfg->getPoxtFix().GetLength();
		if(strURL.Right(nLen)!=cfg->getPoxtFix())
		{
			return false;
		}
	}

	//将不是绝对路径的链接变成绝对路径
	TurnToAbsolutePath(strURL);

	if(!(cfg->getImgUrl().IsEmpty()))
	{
		if(strURL.Find(cfg->getImgUrl())==-1)
		{
			return false;
		}
	}
	
	return true;
}

void Filter::GetImgUrlFromHTML(CString strHtml)
{
	int nBeginPos = 0;
	CString strTagContent;
	CString strAttContent;
	
	if(cfg->getIsParseAll())
	{
		GetImgUrlFromHTTP(strHtml);
		return;
	}
	while(GetTagFromHTML(strHtml,cfg->getTag(),nBeginPos,strTagContent))
	{
		//标签包含关键字判断
		if(!(cfg->getTagKey().IsEmpty()))
		{
			if(strTagContent.Find(cfg->getTagKey())==-1)
			{
				continue;
			}
		}
		if(GetAttrFromTag(strTagContent,cfg->getAttr(),strAttContent))
		{
			if(CheckImgUrl(strAttContent))
			{
				if(ulist->queryImgUrLFromMark(strAttContent))
				{
					ulist->getOrAddWaitDownImgUrl(TRUE,strAttContent);
				}
			}
		}
	}
}

bool Filter::CheckPageUrl(CString &strURL)
{
	strURL.Remove('<');
	strURL.Remove('>');

	//将不是绝对路径的链接变成绝对路径
	TurnToAbsolutePath(strURL);

	if(!cfg->getPageUrl().IsEmpty())
	{
		if(strURL.Find(cfg->getPageUrl())==-1)
		{
			return false;
		}
	}
	if(strURL==L" "||strURL.FindOneOf(L";\\#")!=-1||strURL.FindOneOf(L".\\")==-1)
	{
		return false;
	}
	return true;
}

void Filter::GetPageUrlFromHTML(CString &strHtml)
{
	int nBeginPos = 0;
	CString strTagContent;
	CString strAttContent;
	
	while(GetTagFromHTML(strHtml,L"a",nBeginPos,strTagContent))
	{
		if(GetAttrFromTag(strTagContent,L"href",strAttContent))
		{
			if(CheckPageUrl(strAttContent))
			{
				if(ulist->queryPageUrLFromMark(strAttContent))
				{
					ulist->getOrAddWaitDownPageUrl(TRUE,strAttContent);
				}
			}
		}
	}
}

void Filter::TurnToAbsolutePath(CString &path)
{
	if(path.Find(L"javascript")!=-1)
	{
		return;
	}
	if((path.Left(7)!=L"http://")&&(path.Left(8)!=L"https://"))
	{
		if(path.GetAt(0)==L'/')
		{
			path = cfg->getHostPath() + path;
		}
		else{
			path = cfg->getHostPath() + L"/" + path;
		}
	}

}

void Filter::GetImgUrlFromHTTP(CString &strHtml)
{

}