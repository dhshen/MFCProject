#include "StdAfx.h"
#include "URLList.h"

URLList::URLList(void)
{
	s_PageUrlMark.RemoveAll();
	s_ImgUrlMark.RemoveAll();
	s_waitDownImgUrl.RemoveAll();
	s_waitDownPageUrl.RemoveAll();

	HaveDownPage=0;
	HaveDownImg=0;
	WaitDownPage=0;
	WaitDownImg=0;

	a_hMutex = CreateMutex( NULL,FALSE, NULL );
	b_hMutex = CreateMutex( NULL,FALSE, NULL );
	c_hMutex = CreateMutex( NULL,FALSE, NULL );
	d_hMutex = CreateMutex( NULL,FALSE, NULL );
	e_hMutex = CreateMutex( NULL,FALSE, NULL );
}

//WaitForSingleObject(g_hMutex, INFINITE );
//ReleaseMutex( g_hMutex );

URLList::~URLList(void)
{
}


BOOL URLList::queryPageUrLFromMark(CString &str)
{
	if(this->s_PageUrlMark.Find(str) != NULL)
	{
		return FALSE;
	}
	this->s_PageUrlMark.AddTail(str);
	return TRUE;
}

BOOL URLList::queryImgUrLFromMark(CString &str)
{
	if(this->s_ImgUrlMark.Find(str) != NULL)
	{
		return FALSE;
	}
	this->s_ImgUrlMark.AddTail(str);
	return TRUE;
}

void URLList::getOrAddWaitDownImgUrl(BOOL type,CString &str)
{
	if(type)
	{
		this->s_waitDownImgUrl.AddTail(str);
		WaitDownImg++;
	}
	else{
		str = this->s_waitDownImgUrl.GetHead();
		this->s_waitDownImgUrl.RemoveHead();
		HaveDownImg++;
		WaitDownImg--;
	}
}

void URLList::getOrAddWaitDownPageUrl(BOOL type,CString &str)
{
	if(type)
	{
		this->s_waitDownPageUrl.AddTail(str);
		WaitDownPage++;
	}
	else{
		str = this->s_waitDownPageUrl.GetHead();
		this->s_waitDownPageUrl.RemoveHead();
		HaveDownPage++;
		WaitDownPage--;
	}
}


int URLList::getHaveDownPage()
{
	return HaveDownPage;
}
int URLList::getHaveDownImg()
{
	return HaveDownImg;
}
int URLList::getWaitDownPage()
{
	return WaitDownPage;
}
int URLList::getWaitDownImg()
{
	return WaitDownImg;
}