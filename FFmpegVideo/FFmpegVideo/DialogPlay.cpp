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
		if (nRet == 0)
		{
			m_playBtn.SetWindowText("ֹͣ");
		}
	}
	else
	{
		CCenterManager::GetInstance()->Stop();
		m_playBtn.SetWindowText("����");
	}

	

}
