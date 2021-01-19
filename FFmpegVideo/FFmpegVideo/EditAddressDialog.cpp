// EditAddressDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FFmpegVideo.h"
#include "EditAddressDialog.h"
#include "afxdialogex.h"


// CEditAddressDialog �Ի���

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


// CEditAddressDialog ��Ϣ�������


BOOL CEditAddressDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_addressEdit.SetWindowText(m_fileName.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CEditAddressDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	m_addressEdit.GetWindowText(str);

	m_fileName = str;

	CDialog::OnOK();

}
