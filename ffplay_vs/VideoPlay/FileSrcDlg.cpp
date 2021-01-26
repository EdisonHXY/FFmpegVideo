// FileSrcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoPlay.h"
#include "FileSrcDlg.h"
#include "afxdialogex.h"


// CFileSrcDlg �Ի���

IMPLEMENT_DYNAMIC(CFileSrcDlg, CDialogEx)

CFileSrcDlg::CFileSrcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CFileSrcDlg::~CFileSrcDlg()
{
}

void CFileSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SRC, m_listCtral);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_fileEdit);
}


BEGIN_MESSAGE_MAP(CFileSrcDlg, CDialogEx)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CFileSrcDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_BUTTON1, &CFileSrcDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SRC, &CFileSrcDlg::OnLvnItemchangedListSrc)
END_MESSAGE_MAP()


// CFileSrcDlg ��Ϣ�������


BOOL CFileSrcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_listCtral.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_listCtral.SetExtendedStyle(m_listCtral.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ����   
	m_listCtral.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width(), 0);

	int nIndex = 0;
	m_listCtral.DeleteAllItems();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CFileSrcDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������




}


void CFileSrcDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	m_fileEdit.GetWindowText(str);

	if (str.GetLength() > 0)
	{
		
		m_listCtral.InsertItem(m_listCtral.GetItemCount(),str);

	}


}


void CFileSrcDlg::OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString str = m_listCtral.GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	std::string urlStr = str;
	::SendMessage(GetParent()->GetParent()->m_hWnd, WM_CHANGEVIDEO, 0, (LPARAM)urlStr.c_str());

}
