// LiveSrcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoPlay.h"
#include "LiveSrcDlg.h"
#include "afxdialogex.h"


// CLiveSrcDlg �Ի���

IMPLEMENT_DYNAMIC(CLiveSrcDlg, CDialogEx)

CLiveSrcDlg::CLiveSrcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CLiveSrcDlg::~CLiveSrcDlg()
{
}

void CLiveSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SRC, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLiveSrcDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SRC, &CLiveSrcDlg::OnLvnItemchangedListSrc)
END_MESSAGE_MAP()


// CLiveSrcDlg ��Ϣ�������

void CLiveSrcDlg::InitListUI()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_listCtrl.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ����   
	m_listCtrl.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width(), 0);

	int nIndex = 0;
	m_listCtrl.DeleteAllItems();
	for (auto iter = m_srcMapList.begin();iter != m_srcMapList.end();iter++)
	{
		CString tmpStr =iter->first.c_str();
		m_listCtrl.InsertItem(nIndex,tmpStr);
		nIndex++;
	}

}
BOOL CLiveSrcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_srcMapList.clear();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	string preSrc = "rtmp://58.200.131.2:1935/livetv/";

	m_srcMapList.push_back(make_pair("CCTV-1�ۺ�", preSrc + "cctv1hd"));
	m_srcMapList.push_back(make_pair("CCTV-2�ƾ�", preSrc + "cctv2hd"));
	m_srcMapList.push_back(make_pair("CCTV-3����", preSrc + "cctv3hd"));
	m_srcMapList.push_back(make_pair("CCTV-4���Ĺ���", preSrc + "cctv4hd"));
	m_srcMapList.push_back(make_pair("CCTV-5����", preSrc + "cctv5hd"));
	m_srcMapList.push_back(make_pair("CCTV-6��Ӱ", preSrc + "cctv6hd"));
	m_srcMapList.push_back(make_pair("CCTV-7����ũҵ", preSrc + "cctv7hd"));
	m_srcMapList.push_back(make_pair("CCTV-8���Ӿ�", preSrc + "cctv8hd"));
	m_srcMapList.push_back(make_pair("CCTV-9��¼", preSrc + "cctv9hd"));
	m_srcMapList.push_back(make_pair("CCTV-10�ƽ�", preSrc + "cctv10hd"));
	m_srcMapList.push_back(make_pair("CCTV-11Ϸ��", preSrc + "cctv11hd"));
	m_srcMapList.push_back(make_pair("CCTV-12����뷨", preSrc + "cctv12hd"));
	m_srcMapList.push_back(make_pair("CCTV-13����", preSrc + "cctv13hd"));
	m_srcMapList.push_back(make_pair("CCTV-14�ٶ�", preSrc + "cctv14hd"));
	m_srcMapList.push_back(make_pair("CCTV-15����", preSrc + "cctv15hd"));
	/*m_srcMapList.push_back(make_pair("CCTV-��һ�糡", preSrc + "dyjctv"));
	m_srcMapList.push_back(make_pair("CCTV-��������", preSrc + "gfjstv"));
	m_srcMapList.push_back(make_pair("CCTV-���ɾ糡", preSrc + "hjjctv"));
	m_srcMapList.push_back(make_pair("CCTV-���ƾ糡", preSrc + "fyjctv"));
	m_srcMapList.push_back(make_pair("CCTV-��������", preSrc + "fyzqtv"));
	m_srcMapList.push_back(make_pair("CCTV-��������", preSrc + "fyyytv"));
	m_srcMapList.push_back(make_pair("CCTV-�������", preSrc + "sjdltv"));*/
	
	m_srcMapList.push_back(make_pair("��������HD", preSrc + "btv1hd"));
	m_srcMapList.push_back(make_pair("����Ӱ��HD", preSrc + "btv4hd"));
	m_srcMapList.push_back(make_pair("��������HD", preSrc + "btv6hd"));
	m_srcMapList.push_back(make_pair("��������HD", preSrc + "btv9hd"));
	m_srcMapList.push_back(make_pair("������ʵHD", preSrc + "btv11hd"));

	
	m_srcMapList.push_back(make_pair("��������", preSrc + "ahtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "bttv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "cqtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "dftv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "dntv"));
	m_srcMapList.push_back(make_pair("�㶫����", preSrc + "gdtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "gxtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "gstv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "gztv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "hbtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "hunantv"));
	m_srcMapList.push_back(make_pair("�ӱ�����", preSrc + "hebtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "hntv"));
	m_srcMapList.push_back(make_pair("����������", preSrc + "hljtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "jstv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "jxtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "jltv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "lntv"));
	m_srcMapList.push_back(make_pair("���ɹ�����", preSrc + "nmtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "nxtv"));
	m_srcMapList.push_back(make_pair("�ຣ����", preSrc + "qhtv"));
	m_srcMapList.push_back(make_pair("�Ĵ�����", preSrc + "sctv"));
	m_srcMapList.push_back(make_pair("ɽ������", preSrc + "sdtv"));
	m_srcMapList.push_back(make_pair("ɽ������", preSrc + "sxrtv"));
	m_srcMapList.push_back(make_pair("��������", preSrc + "sxtv"));
	m_srcMapList.push_back(make_pair("ɽ������", preSrc + "sdetv"));
	m_srcMapList.push_back(make_pair("�й�����-1", preSrc + "cetv1"));
	m_srcMapList.push_back(make_pair("�й�����-3", preSrc + "cetv3"));
	m_srcMapList.push_back(make_pair("�й�����-4", preSrc + "cetv4"));


	InitListUI();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CLiveSrcDlg::OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString str = m_listCtrl.GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	const char* urlStr = "";
	for (int i = 0;i<m_srcMapList.size();++i)
	{
		if (m_srcMapList[i].first.c_str() == str)
		{
			urlStr = m_srcMapList[i].second.c_str();
			break;
		}
	}
	::SendMessage(GetParent()->GetParent()->m_hWnd,WM_CHANGEVIDEO, 0, (LPARAM)urlStr);

}
