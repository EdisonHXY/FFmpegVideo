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
	DDX_Control(pDX, IDC_CHECK1, m_loopBtn);
	DDX_Control(pDX, IDC_BUTTON1, m_pauseBtn);
	DDX_Control(pDX, IDC_STATIC_Time, m_timeLenStatic);
	DDX_Control(pDX, IDC_SLIDER1, m_processSlider);
	DDX_Control(pDX, IDC_STATIC_Time2, m_startTimeStatic);
}


BEGIN_MESSAGE_MAP(CDialogPlay, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Play, &CDialogPlay::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_CHECK1, &CDialogPlay::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogPlay::OnBnClickedButton1)
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
		if (CCenterManager::GetInstance()->GetPlayStatus() == PLAYSTATUE_FF_PAUSE)
		{
			CCenterManager::GetInstance()->ContinuePlay();
		}
		else
		{
			int nRet = CCenterManager::GetInstance()->Play(strUrl, m_showZone.GetSafeHwnd(), rc);

			::WritePrivateProfileString("SYS", "PATH", strUrl, m_iniPath);
		}

		
	

	}
	else
	{
		CCenterManager::GetInstance()->Stop();
		
	}

	

}

void CDialogPlay::SetTimeInfo(int nTime, bool bStart)
{
	CString strTime = "00:00:00";
	if (nTime  > 0)
	{
		int nHour = nTime / 3600;
		int nMin = nTime % 3600 / 60;
		int  nSec = nTime % 3600 % 60;

		strTime.Format("%02d:%02d:%02d", nHour, nMin, nSec);

	}
	if (bStart)
	{
		m_startTimeStatic.SetWindowText(strTime);
	}
	else
	{
		m_timeLenStatic.SetWindowText(strTime);
	}
	


}

void CDialogPlay::StatusPlayCallBack(PLAYSTATUE_FF ss, void *lParam)
{
	CDialogPlay *p = (CDialogPlay*)lParam;
	switch (ss)
	{
	case PLAYSTATUE_FF_ING:
	{	
		p->m_playBtn.SetWindowText("停止");
		p->m_pauseBtn.ShowWindow(TRUE);
		int nTime = CCenterManager::GetInstance()->GetPlayDuration();
		p->SetTimeInfo(nTime,false);
		//初始化 进度条
		p->m_processSlider.SetRange(0, nTime);
		
		break;
	}
	case PLAYSTATUE_FF_STOP:
	case PLAYSTATUE_FF_PAUSE:
	case PLAYSTATUE_FF_Finish:
	{
		p->m_playBtn.SetWindowText("播放");
		p->m_pauseBtn.ShowWindow(false);
		if (ss != PLAYSTATUE_FF_PAUSE)
		{
			p->SetTimeInfo(0, false);
			p->SetTimeInfo(0, true);
			p->m_processSlider.SetPos(0);
		}
	
		
		break;
	}
	default:
		break;
	}
}

void CDialogPlay::ProcessPlayCallBack(int nCurrentTime, int nTotalTime, void *lParam)
{
	CDialogPlay *p = (CDialogPlay*)lParam;

	p->m_processSlider.SetPos(nCurrentTime);
	p->SetTimeInfo(nCurrentTime, true);
}

BOOL CDialogPlay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString dir,fileName;
	CString tmpStr = _tcsrchr(szFilePath, '\\');
	(_tcsrchr(szFilePath, '\\'))[0] = 0;
	dir = szFilePath;
	int iIndex = tmpStr.ReverseFind('.');
	fileName = tmpStr.Mid(1, iIndex - 1);

	m_iniPath = dir + "\\" + "play.ini";
	CString str;
	::GetPrivateProfileString("SYS", "PATH", "", str.GetBuffer(MAX_PATH), MAX_PATH, m_iniPath);

	m_fileUrlEdit.SetWindowText(str);

	CCenterManager::GetInstance()->SetStausCall(StatusPlayCallBack, this);
	CCenterManager::GetInstance()->SetPlayProcessCall(ProcessPlayCallBack, this);

	m_tipEdit.SetWindowText("可播放本地文件\r    udp://@224.3.1.1:1234\r\nrtsp://10.0.1.186");
	m_pauseBtn.ShowWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogPlay::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nRet = m_loopBtn.GetCheck();

	CCenterManager::GetInstance()->SetLoopStatus(nRet);

}


void CDialogPlay::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CCenterManager::GetInstance()->Pause();
}
