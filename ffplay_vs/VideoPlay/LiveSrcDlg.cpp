// LiveSrcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoPlay.h"
#include "LiveSrcDlg.h"
#include "afxdialogex.h"


// CLiveSrcDlg 对话框

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


// CLiveSrcDlg 消息处理程序

void CLiveSrcDlg::InitListUI()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_listCtrl.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加   
	m_listCtrl.InsertColumn(0, _T("名称"), LVCFMT_CENTER, rect.Width(), 0);

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
	// TODO:  在此添加额外的初始化
	string preSrc = "rtmp://58.200.131.2:1935/livetv/";

	m_srcMapList.push_back(make_pair("CCTV-1综合", preSrc + "cctv1hd"));
	m_srcMapList.push_back(make_pair("CCTV-2财经", preSrc + "cctv2hd"));
	m_srcMapList.push_back(make_pair("CCTV-3综艺", preSrc + "cctv3hd"));
	m_srcMapList.push_back(make_pair("CCTV-4中文国际", preSrc + "cctv4hd"));
	m_srcMapList.push_back(make_pair("CCTV-5体育", preSrc + "cctv5hd"));
	m_srcMapList.push_back(make_pair("CCTV-6电影", preSrc + "cctv6hd"));
	m_srcMapList.push_back(make_pair("CCTV-7军事农业", preSrc + "cctv7hd"));
	m_srcMapList.push_back(make_pair("CCTV-8电视剧", preSrc + "cctv8hd"));
	m_srcMapList.push_back(make_pair("CCTV-9记录", preSrc + "cctv9hd"));
	m_srcMapList.push_back(make_pair("CCTV-10科教", preSrc + "cctv10hd"));
	m_srcMapList.push_back(make_pair("CCTV-11戏曲", preSrc + "cctv11hd"));
	m_srcMapList.push_back(make_pair("CCTV-12社会与法", preSrc + "cctv12hd"));
	m_srcMapList.push_back(make_pair("CCTV-13新闻", preSrc + "cctv13hd"));
	m_srcMapList.push_back(make_pair("CCTV-14少儿", preSrc + "cctv14hd"));
	m_srcMapList.push_back(make_pair("CCTV-15音乐", preSrc + "cctv15hd"));
	/*m_srcMapList.push_back(make_pair("CCTV-第一剧场", preSrc + "dyjctv"));
	m_srcMapList.push_back(make_pair("CCTV-国防军事", preSrc + "gfjstv"));
	m_srcMapList.push_back(make_pair("CCTV-怀旧剧场", preSrc + "hjjctv"));
	m_srcMapList.push_back(make_pair("CCTV-风云剧场", preSrc + "fyjctv"));
	m_srcMapList.push_back(make_pair("CCTV-风云足球", preSrc + "fyzqtv"));
	m_srcMapList.push_back(make_pair("CCTV-风云音乐", preSrc + "fyyytv"));
	m_srcMapList.push_back(make_pair("CCTV-世界地理", preSrc + "sjdltv"));*/
	
	m_srcMapList.push_back(make_pair("北京卫视HD", preSrc + "btv1hd"));
	m_srcMapList.push_back(make_pair("北京影视HD", preSrc + "btv4hd"));
	m_srcMapList.push_back(make_pair("北京体育HD", preSrc + "btv6hd"));
	m_srcMapList.push_back(make_pair("北京新闻HD", preSrc + "btv9hd"));
	m_srcMapList.push_back(make_pair("北京纪实HD", preSrc + "btv11hd"));

	
	m_srcMapList.push_back(make_pair("安徽卫视", preSrc + "ahtv"));
	m_srcMapList.push_back(make_pair("兵团卫视", preSrc + "bttv"));
	m_srcMapList.push_back(make_pair("重庆卫视", preSrc + "cqtv"));
	m_srcMapList.push_back(make_pair("东方卫视", preSrc + "dftv"));
	m_srcMapList.push_back(make_pair("东南卫视", preSrc + "dntv"));
	m_srcMapList.push_back(make_pair("广东卫视", preSrc + "gdtv"));
	m_srcMapList.push_back(make_pair("广西卫视", preSrc + "gxtv"));
	m_srcMapList.push_back(make_pair("甘肃卫视", preSrc + "gstv"));
	m_srcMapList.push_back(make_pair("贵州卫视", preSrc + "gztv"));
	m_srcMapList.push_back(make_pair("湖北卫视", preSrc + "hbtv"));
	m_srcMapList.push_back(make_pair("湖南卫视", preSrc + "hunantv"));
	m_srcMapList.push_back(make_pair("河北卫视", preSrc + "hebtv"));
	m_srcMapList.push_back(make_pair("河南卫视", preSrc + "hntv"));
	m_srcMapList.push_back(make_pair("黑龙江卫视", preSrc + "hljtv"));
	m_srcMapList.push_back(make_pair("江苏卫视", preSrc + "jstv"));
	m_srcMapList.push_back(make_pair("江西卫视", preSrc + "jxtv"));
	m_srcMapList.push_back(make_pair("吉林卫视", preSrc + "jltv"));
	m_srcMapList.push_back(make_pair("辽宁卫视", preSrc + "lntv"));
	m_srcMapList.push_back(make_pair("内蒙古卫视", preSrc + "nmtv"));
	m_srcMapList.push_back(make_pair("宁夏卫视", preSrc + "nxtv"));
	m_srcMapList.push_back(make_pair("青海卫视", preSrc + "qhtv"));
	m_srcMapList.push_back(make_pair("四川卫视", preSrc + "sctv"));
	m_srcMapList.push_back(make_pair("山东卫视", preSrc + "sdtv"));
	m_srcMapList.push_back(make_pair("山西卫视", preSrc + "sxrtv"));
	m_srcMapList.push_back(make_pair("陕西卫视", preSrc + "sxtv"));
	m_srcMapList.push_back(make_pair("山东教育", preSrc + "sdetv"));
	m_srcMapList.push_back(make_pair("中国教育-1", preSrc + "cetv1"));
	m_srcMapList.push_back(make_pair("中国教育-3", preSrc + "cetv3"));
	m_srcMapList.push_back(make_pair("中国教育-4", preSrc + "cetv4"));


	InitListUI();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLiveSrcDlg::OnLvnItemchangedListSrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
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
