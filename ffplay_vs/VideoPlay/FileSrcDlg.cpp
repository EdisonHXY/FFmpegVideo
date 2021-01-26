// FileSrcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoPlay.h"
#include "FileSrcDlg.h"
#include "afxdialogex.h"


// CFileSrcDlg 对话框

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


// CFileSrcDlg 消息处理程序


BOOL CFileSrcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_listCtral.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_listCtral.SetExtendedStyle(m_listCtral.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加   
	m_listCtral.InsertColumn(0, _T("名称"), LVCFMT_CENTER, rect.Width(), 0);

	int nIndex = 0;
	m_listCtral.DeleteAllItems();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFileSrcDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码




}


void CFileSrcDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString str = m_listCtral.GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	std::string urlStr = str;
	::SendMessage(GetParent()->GetParent()->m_hWnd, WM_CHANGEVIDEO, 0, (LPARAM)urlStr.c_str());

}
