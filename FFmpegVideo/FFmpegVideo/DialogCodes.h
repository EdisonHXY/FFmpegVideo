#pragma once
#include "afxwin.h"
#include "EditAddressDialog.h"
#include <vector>
#include "FFmpeg/FFmpeg_Play.h"
using namespace std;
// CDialogCodes 对话框


class CDialogCodes : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCodes)

public:
	CDialogCodes(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogCodes();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Code };
#endif
	CEditAddressDialog m_showDlg;
	CString ShowEditDlg(int nIndex, CWnd *wnd);
	vector<CFFmpeg_Play *> m_controlList;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CStatic m_showStatic0;
	CStatic m_showStatic1;
	CStatic m_showStatic2;
	CStatic m_showStatic3;
	CStatic m_showStatic4;
	CStatic m_showStatic5;
	afx_msg void OnStnClickedStatic0();
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnStnClickedStatic4();
	afx_msg void OnStnClickedStatic5();
	virtual BOOL OnInitDialog();
};
