// DialogPlay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "DialogPlay.h"
#include "afxdialogex.h"


// CDialogPlay �Ի���

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


// CDialogPlay ��Ϣ�������


void CDialogPlay::OnBnClickedButtonPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTitle;
	m_playBtn.GetWindowText(strTitle);

	CString strUrl;
	m_fileUrlEdit.GetWindowText(strUrl);
	CRect rc;
	m_showZone.GetClientRect(&rc);
	
	if (strTitle == "����")
	{
		int nRet = CCenterManager::GetInstance()->Play(strUrl, m_showZone.GetSafeHwnd(), rc);
	
		::WritePrivateProfileString("SYS", "PATH", strUrl, m_iniPath);

	}
	else
	{
		CCenterManager::GetInstance()->Stop();
		
	}

	

}
void CDialogPlay::StatusPlayCallBack(PLAYSTATUE_FF ss, void *lParam)
{
	CDialogPlay *p = (CDialogPlay*)lParam;
	switch (ss)
	{
	case PLAYSTATUE_FF_ING:
		p->m_playBtn.SetWindowText("ֹͣ");
		break;
	case PLAYSTATUE_FF_STOP:
	case PLAYSTATUE_FF_PAUSE:
	case PLAYSTATUE_FF_Finish:
		p->m_playBtn.SetWindowText("����");
		break;
	default:
		break;
	}
}

BOOL CDialogPlay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
