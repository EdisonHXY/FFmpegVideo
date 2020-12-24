#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "CenterManager.h"

// CDialogPlay �Ի���

class CDialogPlay : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPlay)

public:
	CDialogPlay(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogPlay();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Play };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_tipEdit;
	CButton m_playBtn;
	afx_msg void OnBnClickedButtonPlay();
	CMFCEditBrowseCtrl m_fileUrlEdit;
	CStatic m_showZone;
};