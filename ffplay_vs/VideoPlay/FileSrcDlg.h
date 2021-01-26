#pragma once
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"

#include <string>
using namespace std;
// CFileSrcDlg 对话框

class CFileSrcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSrcDlg)

public:
	CFileSrcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileSrcDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtral;
	CMFCEditBrowseCtrl m_fileEdit;
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult);
};
