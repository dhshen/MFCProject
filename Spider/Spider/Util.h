#pragma once

#include "stdafx.h"
#include "Config.h"
#include "Filter.h"
#include "URLList.h"
#include "SpiderDlg.h"

extern Config *cfg;
extern URLList *ulist;
extern Filter *filter;
extern CSpiderDlg *sp;
extern bool ON_OFF;
extern BOOL isPause;


bool DownLoadImage(CString &strImgUrl);
bool DownLoadPage(CString &strHtml,CString strPageUrl);

UINT StatProc( LPVOID pParam );











