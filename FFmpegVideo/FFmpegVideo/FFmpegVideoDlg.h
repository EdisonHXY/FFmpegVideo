
// FFmpegVideoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "DialogPlay.h"
#include "DialogCodes.h"
#include <vector>
using namespace std;
// CFFmpegVideoDlg �Ի���
class CFFmpegVideoDlg : public CDialogEx
{
// ����
public:
	CFFmpegVideoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FFMPEGVIDEO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void InitTabUI(); //��ʼ�� tab ui
	void ChangeTab(UINT nIndex);

// ʵ��
protected:
	HICON m_hIcon;
	CDialogPlay m_playDlg;
	CDialogCodes m_codesDlg;
	vector<CDialogEx *> m_dlgList;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tablCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
