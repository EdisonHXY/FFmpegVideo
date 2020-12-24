
// FFmpegVideoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "DialogPlay.h"
#include "DialogCodes.h"
#include <vector>
using namespace std;
// CFFmpegVideoDlg 对话框
class CFFmpegVideoDlg : public CDialogEx
{
// 构造
public:
	CFFmpegVideoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FFMPEGVIDEO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void InitTabUI(); //初始化 tab ui
	void ChangeTab(UINT nIndex);

// 实现
protected:
	HICON m_hIcon;
	CDialogPlay m_playDlg;
	CDialogCodes m_codesDlg;
	vector<CDialogEx *> m_dlgList;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tablCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
