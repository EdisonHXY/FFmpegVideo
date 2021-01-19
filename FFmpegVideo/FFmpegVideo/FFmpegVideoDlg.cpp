
// FFmpegVideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "FFmpegVideoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFFmpegVideoDlg 对话框



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
	m_tablCtrl.InsertItem(0, "播放");
	m_tablCtrl.InsertItem(1, "6画面");

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


// CFFmpegVideoDlg 消息处理程序

BOOL CFFmpegVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CFFmpeg_Play::InitData();

	// TODO: 在此添加额外的初始化代码
	InitTabUI();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFFmpegVideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFFmpegVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFFmpegVideoDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int nCurSel = m_tablCtrl.GetCurSel();
	ChangeTab(nCurSel);
}
