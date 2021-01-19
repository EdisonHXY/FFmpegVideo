
// FFmpegVideoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "FFmpegVideoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CFFmpegVideoDlg �Ի���



CFFmpegVideoDlg::CFFmpegVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FFMPEGVIDEO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFFmpegVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tablCtrl);
}

void CFFmpegVideoDlg::InitTabUI()
{
	m_tablCtrl.InsertItem(0, "����");
	m_tablCtrl.InsertItem(1, "6����");

	CRect rc;
	m_tablCtrl.GetWindowRect(&rc);

	m_playDlg.Create(IDD_DIALOG_Play, &m_tablCtrl);
	m_codesDlg.Create(IDD_DIALOG_Code, &m_tablCtrl);
	rc.left -= 20;
	rc.top -= 20;
	m_playDlg.MoveWindow(rc);
	m_codesDlg.MoveWindow(rc);

	m_dlgList.push_back(&m_playDlg);
	m_dlgList.push_back(&m_codesDlg);

	m_tablCtrl.SetCurSel(0);
	ChangeTab(0);
}

void CFFmpegVideoDlg::ChangeTab(UINT nIndex)
{
	if (nIndex >= m_dlgList.size())
	{
		nIndex = 0;
	}

	for (int i =0 ;i < m_dlgList.size();++i)
	{
		m_dlgList[i]->ShowWindow(nIndex == i);
	}

}

BEGIN_MESSAGE_MAP(CFFmpegVideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFFmpegVideoDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CFFmpegVideoDlg ��Ϣ�������

BOOL CFFmpegVideoDlg::OnInitDialog()
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

	CFFmpeg_Play::InitData();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitTabUI();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFFmpegVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFFmpegVideoDlg::OnPaint()
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
HCURSOR CFFmpegVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFFmpegVideoDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int nCurSel = m_tablCtrl.GetCurSel();
	ChangeTab(nCurSel);
}
