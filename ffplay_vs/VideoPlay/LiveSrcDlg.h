#pragma once
#include "afxcmn.h"
#include <map>
#include <vector>
using namespace std;
// CLiveSrcDlg 对话框

class CLiveSrcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLiveSrcDlg)

public:
	CLiveSrcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLiveSrcDlg();


	vector< pair<string, string> >m_srcMapList;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void InitListUI();
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtrl;
	afx_msg void OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult);
};
