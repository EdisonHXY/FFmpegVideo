#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "CenterManager.h"
#include "afxcmn.h"

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
	CString m_iniPath;
	afx_msg void OnBnClickedButtonPlay();
	void SetTimeInfo(int nTime,bool bStart);
	static void StatusPlayCallBack(PLAYSTATUE_FF ss, void *lParam);
	static void ProcessPlayCallBack(int nCurrentTime, int nTotalTime, void *lParam);
	CMFCEditBrowseCtrl m_fileUrlEdit;
	CStatic m_showZone;
	virtual BOOL OnInitDialog();
	CButton m_loopBtn;
	afx_msg void OnBnClickedCheck1();
	CButton m_pauseBtn;
	afx_msg void OnBnClickedButton1();
	CStatic m_timeLenStatic;
	CSliderCtrl m_processSlider;
	CStatic m_startTimeStatic;
};
