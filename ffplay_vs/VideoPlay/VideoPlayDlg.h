
// VideoPlayDlg.h : 头文件
//

#pragma once
#include "ffplay++/FFPlay.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
#include "FileSrcDlg.h"
#include "LiveSrcDlg.h"
#include <vector>
using namespace std;
// CVideoPlayDlg 对话框
class CVideoPlayDlg : public CDialogEx
{
// 构造
public:
	CVideoPlayDlg(CWnd* pParent = NULL);	// 标准构造函数

	CFFPlay m_play;
	CFileSrcDlg m_fileDlg;
	CLiveSrcDlg m_liveDlg;
	vector<CDialogEx *> m_dlgList;

	CString m_currentFile;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEOPLAY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void SetTimeInfo(int nTime, bool bStart);
	bool m_bPauseIng;
	
	static void StatusPlayCallBack(PLAYSTATUE_FF ss, void *lParam);
	static void ProcessPlayCallBack(double nCurrentTime, double nTotalTime, void *lParam);

	void ChangeTab(UINT nIndex);
	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CStatic m_showEdit;
	
	CButton m_playBtn;
	CButton m_stopBtn;
	CButton m_forwordBtn;
	CButton m_backBtn;
	CButton m_loopBtn;
	CSliderCtrl m_proSliderCtrl;
	CStatic m_time1Static;
	CStatic m_time2Static;
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonForword();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedCheckLoop();

	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_muteBtn;
	afx_msg void OnBnClickedCheckLoop2();
	afx_msg void OnBnClickedButtonStop();
	CSliderCtrl m_volueSliderCtrl;
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tabCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnChangevideo(WPARAM wParam, LPARAM lParam);
};
