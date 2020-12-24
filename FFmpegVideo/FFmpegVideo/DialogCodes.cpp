// DialogCodes.cpp : 实现文件
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "DialogCodes.h"
#include "afxdialogex.h"


// CDialogCodes 对话框

IMPLEMENT_DYNAMIC(CDialogCodes, CDialogEx)

CDialogCodes::CDialogCodes(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Code, pParent)
{

}

CDialogCodes::~CDialogCodes()
{
}

void CDialogCodes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogCodes, CDialogEx)
END_MESSAGE_MAP()


// CDialogCodes 消息处理程序
