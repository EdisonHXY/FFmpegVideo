#pragma once
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"

#include <string>
using namespace std;
// CFileSrcDlg �Ի���

class CFileSrcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSrcDlg)

public:
	CFileSrcDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileSrcDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtral;
	CMFCEditBrowseCtrl m_fileEdit;
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult);
};
