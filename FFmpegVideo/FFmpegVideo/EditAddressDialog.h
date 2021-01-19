#pragma once
#include "afxeditbrowsectrl.h"

#include <string>
using namespace std;
// CEditAddressDialog �Ի���

class CEditAddressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEditAddressDialog)

public:
	CEditAddressDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditAddressDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

	std::string m_fileName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMFCEditBrowseCtrl m_addressEdit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
