
// FFmpegVideo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFFmpegVideoApp: 
// �йش����ʵ�֣������ FFmpegVideo.cpp
//

class CFFmpegVideoApp : public CWinApp
{
public:
	CFFmpegVideoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFFmpegVideoApp theApp;