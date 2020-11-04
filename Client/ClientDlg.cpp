
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define port 8000


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg 对话框



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
	, m_DataSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Concect, m_ConPC);
	DDX_Text(pDX, IDC_DataSend, m_DataSend);
	DDX_Control(pDX, IDC_MESGE, m_event);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ServerIP);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Concect, &CClientDlg::OnBnClickedConcect)
	ON_BN_CLICKED(IDC_Send, &CClientDlg::OnBnClickedSend)
	ON_EN_CHANGE(IDC_DataReceive, &CClientDlg::OnEnChangeDatareceive)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	//m_event = (CEdit *)GetDlgItem(IDC_MESGE);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{


	CPaintDC dc(this);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1); //这个IDB_BITMAP2要自己添加
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 1000, 600);// 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);


	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedConcect()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_connect)                             // 如果已经连接，则断开服务器

	{

		m_connect = false;

		pSock->Close();

		delete pSock;

		pSock = NULL;

		m_ConPC.SetWindowTextW(_T("连接服务器"));

		UpdateData(false);

		return;

	}

	else                                                // 未连接，则连接服务器

	{

		pSock = new CClientSocket();

		if (!pSock->Create())         //创建套接字

		{

			AfxMessageBox(_T("创建套接字失败！"));

			return;

		}

	}

	BYTE nFild[4];
	CString sIP;

	m_ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format(L"%d.%d.%d.%d", nFild[0], nFild[1], nFild[2], nFild[3]); //IP地址



	CString strText(_T(""));
	GetDlgItemText(IDC_EDIT1, strText);
	//double val1 = _tcstod(strText, NULL); // 浮点数用这个   
	short m_port = _ttoi(strText); // 整数用这个



	if (!pSock->Connect(sIP, m_port))
	//if (!pSock->Connect(_T("127.0.0.1"), port))    //连接服务器

	{

		AfxMessageBox(_T("连接服务器失败！"));

		return;

	}

	else

	{

		m_connect = true;

		m_ConPC.SetWindowTextW(_T("断开服务器"));

		UpdateData(false);

	}
}


void CClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码

	if (!m_connect)return;                               //未连接服务器则不执行

	UpdateData(true);                                     //获取界面数据

	if (m_DataSend != "")

	{

		char* pBuff = new char[m_DataSend.GetLength() * 2];

		memset(pBuff, 0, m_DataSend.GetLength() * 2);

		//IDC_DataSend
		CString  str;

		GetDlgItemText(IDC_DataSend, str);



		WChar2MByte(m_DataSend.GetBuffer(0), pBuff, m_DataSend.GetLength() * 2);

		//strcpy(pBuff, str.c_str());

		USES_CONVERSION;
		//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
		char * Tempstr = T2A(str);

		//strcpy(pBuff, str.GetBuffer(0));

		pSock->SendMSG(Tempstr, m_DataSend.GetLength() * 2);


	//	RecvData(CClientSocket* pSocket);



		
		CString str1 = L"我说：";
	

		str1 += str;

		UpdateEvent(str1);


	}


}



BOOL CClientDlg::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)

{

	int n = 0;

	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);

	if (n<nlen)return FALSE;

	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);

	return TRUE;

}


BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)

{

	switch (pMsg->wParam)

	{

	case VK_RETURN:

	case VK_ESCAPE:

		return true; break;

	}

	return CDialogEx::PreTranslateMessage(pMsg);

}

void CClientDlg::OnEnChangeDatareceive()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CClientDlg::RecvData(CClientSocket* pSocket)
{

	char* pData = NULL;

	pData = new char[1024];

	memset(pData, 0, sizeof(char) * 1024);

	UCHAR leng = 0;

	CString str;

	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)

	{

		str = pData;


		//USES_CONVERSION;
		//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
		//char * pFileName = T2A(str);
		//OUTINFO_1_PARAM("---%s-----\n", pFileName);



		UpdateEvent(str);



	}

	// int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);

	//获取编辑框最后一行索引
	
	//m_event.SetSel(lastLine + 1, lastLine + 2, 0);

	//选择编辑框最后一行

//	m_event.ReplaceSel(str);




}


/*
void CClientDlg::RecvData(CClientSocket* pSocket)

{

	char* pData = NULL;

	pData = new char[1024];

	memset(pData, 0, sizeof(char) * 1024);

	UCHAR leng = 0;

	CString str;

	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)

	{

		str = pData;


		//USES_CONVERSION;
		//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
		//char * pFileName = T2A(str);
		//OUTINFO_1_PARAM("---%s-----\n", pFileName);



		UpdateEvent(str);

	

	}

	delete pData;

	pData = NULL;

}

*/


void CClientDlg::UpdateEvent(CString str)

{

	CString string;

	CTime time = CTime::GetCurrentTime();

	// 获取系统当前时间

	str += _T("\r\n");

	// 用于换行显示日志

	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;

	// 格式化当前时间


	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);

	//获取编辑框最后一行索引

	m_event.SetSel(lastLine + 1, lastLine + 2, 0);

	//选择编辑框最后一行

	m_event.ReplaceSel(string);                                                             //替换所选那一行的内容

}



HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(235, 64, 50));
		pDC->SetBkMode(TRANSPARENT);
		return  HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
	
}
