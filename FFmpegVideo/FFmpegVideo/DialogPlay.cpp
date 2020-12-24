// DialogPlay.cpp : 实现文件
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "DialogPlay.h"
#include "afxdialogex.h"


// CDialogPlay 对话框

IMPLEMENT_DYNAMIC(CDialogPlay, CDialogEx)

CDialogPlay::CDialogPlay(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Play, pParent)
{

}

CDialogPlay::~CDialogPlay()
{
}

void CDialogPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_tipEdit);
	DDX_Control(pDX, IDC_BUTTON_Play, m_playBtn);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_fileUrlEdit);
	DDX_Control(pDX, IDC_STATIC_SHOW, m_showZone);
}


BEGIN_MESSAGE_MAP(CDialogPlay, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Play, &CDialogPlay::OnBnClickedButtonPlay)
END_MESSAGE_MAP()


// CDialogPlay 消息处理程序


void CDialogPlay::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTitle;
	m_playBtn.GetWindowText(strTitle);

	CString strUrl;
	m_fileUrlEdit.GetWindowText(strUrl);
	CRect rc;
	m_showZone.GetClientRect(&rc);
	
	if (strTitle == "播放")
	{
		int nRet = CCenterManager::GetInstance()->Play(strUrl, m_showZone.GetSafeHwnd(), rc);
		if (nRet == 0)
		{
			m_playBtn.SetWindowText("停止");
		}
	}
	else
	{
		CCenterManager::GetInstance()->Stop();
		m_playBtn.SetWindowText("播放");
	}

	

}
