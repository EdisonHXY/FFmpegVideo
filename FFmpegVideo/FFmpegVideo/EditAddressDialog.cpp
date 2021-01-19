// EditAddressDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "EditAddressDialog.h"
#include "afxdialogex.h"


// CEditAddressDialog 对话框

IMPLEMENT_DYNAMIC(CEditAddressDialog, CDialogEx)

CEditAddressDialog::CEditAddressDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CEditAddressDialog::~CEditAddressDialog()
{
}

void CEditAddressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_addressEdit);
}


BEGIN_MESSAGE_MAP(CEditAddressDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CEditAddressDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEditAddressDialog 消息处理程序


BOOL CEditAddressDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_addressEdit.SetWindowText(m_fileName.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CEditAddressDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	m_addressEdit.GetWindowText(str);

	m_fileName = str;

	CDialog::OnOK();

}
