#pragma once


// CDialogCodes �Ի���

class CDialogCodes : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCodes)

public:
	CDialogCodes(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogCodes();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Code };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
