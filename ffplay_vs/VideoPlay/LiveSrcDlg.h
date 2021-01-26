#pragma once
#include "afxcmn.h"
#include <map>
#include <vector>
using namespace std;
// CLiveSrcDlg �Ի���

class CLiveSrcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLiveSrcDlg)

public:
	CLiveSrcDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLiveSrcDlg();


	vector< pair<string, string> >m_srcMapList;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	void InitListUI();
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtrl;
	afx_msg void OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult);
};
