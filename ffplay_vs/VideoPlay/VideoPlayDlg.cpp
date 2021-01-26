
// VideoPlayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoPlay.h"
#include "VideoPlayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int g_nProo = 0;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoPlayDlg �Ի���



CVideoPlayDlg::CVideoPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEOPLAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIDOE, m_showEdit);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_playBtn);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stopBtn);
	DDX_Control(pDX, IDC_BUTTON_Forword, m_forwordBtn);
	DDX_Control(pDX, IDC_BUTTON_Back, m_backBtn);
	DDX_Control(pDX, IDC_CHECK_Loop, m_loopBtn);
	DDX_Control(pDX, IDC_SLIDER1, m_proSliderCtrl);
	DDX_Control(pDX, IDC_STATIC_Time1, m_time1Static);
	DDX_Control(pDX, IDC_STATIC_Time2, m_time2Static);
	DDX_Control(pDX, IDC_CHECK_Loop2, m_muteBtn);
	DDX_Control(pDX, IDC_SLIDER2, m_volueSliderCtrl);

	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

void CVideoPlayDlg::SetTimeInfo(int nTime, bool bStart)
{
	CString strTime = "00:00:00";
	if (nTime > 0)
	{
		int nHour = nTime / 3600;
		int nMin = nTime % 3600 / 60;
		int  nSec = nTime % 3600 % 60;

		strTime.Format("%02d:%02d:%02d", nHour, nMin, nSec);

	}
	if (bStart)
	{
		m_time1Static.SetWindowText(strTime);
	}
	else
	{
		m_time2Static.SetWindowText(strTime);
	}



}

void CVideoPlayDlg::StatusPlayCallBack(PLAYSTATUE_FF ss, void *lParam)
{
	CVideoPlayDlg * dlg = (CVideoPlayDlg*)lParam;
	if (ss == PLAYSTATUE_FF_STOP)
	{
	
		dlg->m_playBtn.SetWindowText("����");
		dlg->SetTimeInfo(0, false);
		dlg->SetTimeInfo(0, true);
		dlg->m_proSliderCtrl.SetPos(0);

		dlg->m_backBtn.EnableWindow(false);
		dlg->m_forwordBtn.EnableWindow(false);
		dlg->m_stopBtn.EnableWindow(false);
		dlg->m_bPauseIng = false;
	}
	else if (ss == PLAYSTATUE_FF_ING)
	{
		dlg->m_playBtn.SetWindowText("��ͣ");
		dlg->m_backBtn.EnableWindow(true);
		dlg->m_forwordBtn.EnableWindow(true);
		dlg->m_stopBtn.EnableWindow(true);
		dlg->m_bPauseIng = false;
	}
	else if (ss == PLAYSTATUE_FF_PAUSE)
	{
		dlg->m_playBtn.SetWindowText("����");
		dlg->m_bPauseIng = true;
	}

}

void CVideoPlayDlg::ProcessPlayCallBack(double nCurrentTime, double nTotalTime, void *lParam)
{
	CVideoPlayDlg * dlg = (CVideoPlayDlg*)lParam;

	dlg->m_proSliderCtrl.SetRange(0, nTotalTime / 1000000);

	dlg->m_proSliderCtrl.SetPos(nCurrentTime);
	dlg->SetTimeInfo(nCurrentTime, true);
	dlg->SetTimeInfo(nTotalTime/1000000 - nCurrentTime, false);
	g_nProo = nCurrentTime;
}

BEGIN_MESSAGE_MAP(CVideoPlayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CVideoPlayDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_Forword, &CVideoPlayDlg::OnBnClickedButtonForword)
	ON_BN_CLICKED(IDC_BUTTON_Back, &CVideoPlayDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_Loop, &CVideoPlayDlg::OnBnClickedCheckLoop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CVideoPlayDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_CHECK_Loop2, &CVideoPlayDlg::OnBnClickedCheckLoop2)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CVideoPlayDlg::OnBnClickedButtonStop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CVideoPlayDlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CVideoPlayDlg::OnTcnSelchangeTab1)
	ON_MESSAGE(WM_CHANGEVIDEO, &CVideoPlayDlg::OnChangevideo)
END_MESSAGE_MAP()


void CVideoPlayDlg::ChangeTab(UINT nIndex)
{

	if (nIndex >= m_dlgList.size())
	{
		nIndex = 0;
	}

	for (int i = 0;i < m_dlgList.size();++i)
	{
		m_dlgList[i]->ShowWindow(nIndex == i);
	}

}


// CVideoPlayDlg ��Ϣ�������

BOOL CVideoPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CFFPlay::InitFFmpeg();

	m_bPauseIng = false;
	m_volueSliderCtrl.SetRange(0, 128);
	m_volueSliderCtrl.SetPos(128);
	m_play.SetVolumeNum(128);
	m_play.SetStausCall(StatusPlayCallBack, this);
	m_play.SetPlayProcessCall(ProcessPlayCallBack, this);
	
	//��ʼ���б�
	m_tabCtrl.InsertItem(0, "�ļ�");
	m_tabCtrl.InsertItem(1, "ֱ��Դ");

	CRect rc;
	m_tabCtrl.GetWindowRect(&rc);

	m_liveDlg.Create(IDD_DIALOG1, &m_tabCtrl);
	m_fileDlg.Create(IDD_DIALOG2, &m_tabCtrl);

	rc.top -= 20;
	rc.bottom -= 0;
	rc.left = 0;
	rc.right -= 0;

	m_dlgList.push_back(&m_fileDlg);
	m_dlgList.push_back(&m_liveDlg);
	m_liveDlg.MoveWindow(rc);
	m_fileDlg.MoveWindow(rc);

	m_tabCtrl.SetCurSel(0);

	
	ChangeTab(0);
	StatusPlayCallBack(PLAYSTATUE_FF_STOP, this);
	//m_currentFile = m_fileDlg.;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVideoPlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVideoPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVideoPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVideoPlayDlg::OnBnClickedButtonPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;

	m_playBtn.GetWindowText(str);

	if (str == "����")
	{

		if (m_bPauseIng)
		{
			m_play.PauseAndContinuePlay();
		}
		else
		{
 			CRect rc;
			m_showEdit.GetClientRect(rc);
 			m_play.StartPlay(m_currentFile, m_showEdit.GetSafeHwnd(),rc.Width(),rc.Height());
		}


	}
	else
	{
		m_play.PauseAndContinuePlay();
	
	}



	//m_playBtn.SetWindowText(str);

}

bool g_bLoopForword;
bool g_bLoopBack;

int SDL_ThreadFunction1(void *data)
{

	CVideoPlayDlg *dlg = (CVideoPlayDlg*)data;
	while (g_bLoopForword)
	{
		dlg->m_play.FaseForwad(2);
		SDL_Delay(1000);
	}
	
	return 0;
}
int SDL_ThreadFunction_BACK(void *data)
{

	CVideoPlayDlg *dlg = (CVideoPlayDlg*)data;

	while (g_bLoopBack)
	{
		dlg->m_play.BackStep(2);
		SDL_Delay(1000);
	}

	
	return 0;

}

void CVideoPlayDlg::OnBnClickedButtonForword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_forwordBtn.GetWindowText(str);

	if (str == "���")
	{
		str = "�����";
		g_bLoopBack = false;
		g_bLoopForword = true;
		SDL_CreateThread(SDL_ThreadFunction1, "", this);

	}
	else
	{
		g_bLoopForword = false;
		str = "���";
	}

	m_forwordBtn.SetWindowText(str);

}


void CVideoPlayDlg::OnBnClickedButtonBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_backBtn.GetWindowText(str);

	if (str == "����")
	{
		str = "������";
		g_bLoopBack = true;
		g_bLoopForword = false;
		SDL_CreateThread(SDL_ThreadFunction_BACK, "", this);

	}
	else
	{
		g_bLoopBack = false;
		str = "����";
	}

	m_backBtn.SetWindowText(str);
}


void CVideoPlayDlg::OnBnClickedCheckLoop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nCheck = m_loopBtn.GetCheck();

	m_play.SetLoop(nCheck);

}


void CVideoPlayDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nPos = m_proSliderCtrl.GetPos();


	//	m_play.SeekToTime(nPos);
	



}


void CVideoPlayDlg::OnBnClickedCheckLoop2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRet = m_muteBtn.GetCheck();
	
	m_play.VolumeZero();

	
}


void CVideoPlayDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_play.StopPlay();

}


void CVideoPlayDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nRet = m_volueSliderCtrl.GetPos();
	m_play.SetVolumeNum(nRet);
}


void CVideoPlayDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nCurSel = m_tabCtrl.GetCurSel();
	ChangeTab(nCurSel);

}


afx_msg LRESULT CVideoPlayDlg::OnChangevideo(WPARAM wParam, LPARAM lParam)
{
	static string preStr = "";
	string urlPath = (char*)lParam;

	if (preStr == urlPath)
	{
		return 0;
	}

	CRect rc;
	m_showEdit.GetClientRect(rc);
	m_currentFile = urlPath.c_str();
	m_play.StartPlay(urlPath.c_str(), m_showEdit.GetSafeHwnd(), rc.Width(), rc.Height());

	preStr = urlPath;

	return 0;
}
