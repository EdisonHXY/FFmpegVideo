#pragma once
#include "afxeditbrowsectrl.h"

#include <string>
using namespace std;
// CEditAddressDialog 对话框

class CEditAddressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEditAddressDialog)

public:
	CEditAddressDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditAddressDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

	std::string m_fileName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCEditBrowseCtrl m_addressEdit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
