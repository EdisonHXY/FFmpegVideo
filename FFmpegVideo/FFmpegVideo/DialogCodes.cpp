// DialogCodes.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "DialogCodes.h"
#include "afxdialogex.h"


// CDialogCodes �Ի���

IMPLEMENT_DYNAMIC(CDialogCodes, CDialogEx)

CDialogCodes::CDialogCodes(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Code, pParent)
{
	m_showDlg.Create(IDD_DIALOG1, pParent);
	m_controlList.clear();
}

CDialogCodes::~CDialogCodes()
{
}

CString CDialogCodes::ShowEditDlg(int nIndex,CWnd *wnd)
{
	CEditAddressDialog dlg;

	string fileUrl = m_controlList[nIndex]->GetPlayUrl();
	dlg.m_fileName = fileUrl;
	int nR =  dlg.DoModal();

	if (nR == IDOK )
	{
		

		if (dlg.m_fileName != fileUrl)
		{
			//m_controlList[nIndex]->Stop();
			CRect rc;
			wnd->GetClientRect(&rc);
			m_controlList[nIndex]->Play(dlg.m_fileName.c_str(), wnd->GetSafeHwnd(), rc,false);
		}

	}


	return "";
}

void CDialogCodes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC0, m_showStatic0);
	DDX_Control(pDX, IDC_STATIC1, m_showStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_showStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_showStatic3);
	DDX_Control(pDX, IDC_STATIC4, m_showStatic4);
	DDX_Control(pDX, IDC_STATIC5, m_showStatic5);
}


BEGIN_MESSAGE_MAP(CDialogCodes, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
	ON_STN_CLICKED(IDC_STATIC0, &CDialogCodes::OnStnClickedStatic0)
	ON_STN_CLICKED(IDC_STATIC1, &CDialogCodes::OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC2, &CDialogCodes::OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC3, &CDialogCodes::OnStnClickedStatic3)
	ON_STN_CLICKED(IDC_STATIC4, &CDialogCodes::OnStnClickedStatic4)
	ON_STN_CLICKED(IDC_STATIC5, &CDialogCodes::OnStnClickedStatic5)
END_MESSAGE_MAP()


// CDialogCodes ��Ϣ�������

void CDialogCodes::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CDialogCodes::OnStnClickedStatic0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowEditDlg(0,&m_showStatic0);
}


void CDialogCodes::OnStnClickedStatic1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowEditDlg(1, &m_showStatic1);
}


void CDialogCodes::OnStnClickedStatic2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowEditDlg(2, &m_showStatic2);
}


void CDialogCodes::OnStnClickedStatic3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowEditDlg(3, &m_showStatic3);
}


void CDialogCodes::OnStnClickedStatic4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowEditDlg(4, &m_showStatic4);
}


void CDialogCodes::OnStnClickedStatic5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowEditDlg(5, &m_showStatic5);
}


BOOL CDialogCodes::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_controlList.push_back(new CFFmpeg_Play);
	m_controlList.push_back(new CFFmpeg_Play);
	m_controlList.push_back(new CFFmpeg_Play);
	m_controlList.push_back(new CFFmpeg_Play);
	m_controlList.push_back(new CFFmpeg_Play);
	m_controlList.push_back(new CFFmpeg_Play);




	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
