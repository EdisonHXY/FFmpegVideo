#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "CenterManager.h"

// CDialogPlay 对话框

class CDialogPlay : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPlay)

public:
	CDialogPlay(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPlay();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Play };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_tipEdit;
	CButton m_playBtn;
	CString m_iniPath;
	afx_msg void OnBnClickedButtonPlay();
	static void StatusPlayCallBack(PLAYSTATUE_FF ss, void *lParam);
	CMFCEditBrowseCtrl m_fileUrlEdit;
	CStatic m_showZone;
	virtual BOOL OnInitDialog();
};
