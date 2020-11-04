
// ClientDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CClientDlg �Ի���



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


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	//m_event = (CEdit *)GetDlgItem(IDC_MESGE);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
{


	CPaintDC dc(this);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1); //���IDB_BITMAP2Ҫ�Լ����
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 1000, 600);// ��Щ�������Ե���ͼƬ���λ�úʹ�С
	dc.SelectObject(pOldBrush);


	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedConcect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (m_connect)                             // ����Ѿ����ӣ���Ͽ�������

	{

		m_connect = false;

		pSock->Close();

		delete pSock;

		pSock = NULL;

		m_ConPC.SetWindowTextW(_T("���ӷ�����"));

		UpdateData(false);

		return;

	}

	else                                                // δ���ӣ������ӷ�����

	{

		pSock = new CClientSocket();

		if (!pSock->Create())         //�����׽���

		{

			AfxMessageBox(_T("�����׽���ʧ�ܣ�"));

			return;

		}

	}

	BYTE nFild[4];
	CString sIP;

	m_ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format(L"%d.%d.%d.%d", nFild[0], nFild[1], nFild[2], nFild[3]); //IP��ַ



	CString strText(_T(""));
	GetDlgItemText(IDC_EDIT1, strText);
	//double val1 = _tcstod(strText, NULL); // �����������   
	short m_port = _ttoi(strText); // ���������



	if (!pSock->Connect(sIP, m_port))
	//if (!pSock->Connect(_T("127.0.0.1"), port))    //���ӷ�����

	{

		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));

		return;

	}

	else

	{

		m_connect = true;

		m_ConPC.SetWindowTextW(_T("�Ͽ�������"));

		UpdateData(false);

	}
}


void CClientDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (!m_connect)return;                               //δ���ӷ�������ִ��

	UpdateData(true);                                     //��ȡ��������

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
		//���ú�����T2A��W2A��֧��ATL��MFC�е��ַ�ת��
		char * Tempstr = T2A(str);

		//strcpy(pBuff, str.GetBuffer(0));

		pSock->SendMSG(Tempstr, m_DataSend.GetLength() * 2);


	//	RecvData(CClientSocket* pSocket);



		
		CString str1 = L"��˵��";
	

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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		//���ú�����T2A��W2A��֧��ATL��MFC�е��ַ�ת��
		//char * pFileName = T2A(str);
		//OUTINFO_1_PARAM("---%s-----\n", pFileName);



		UpdateEvent(str);



	}

	// int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);

	//��ȡ�༭�����һ������
	
	//m_event.SetSel(lastLine + 1, lastLine + 2, 0);

	//ѡ��༭�����һ��

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
		//���ú�����T2A��W2A��֧��ATL��MFC�е��ַ�ת��
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

	// ��ȡϵͳ��ǰʱ��

	str += _T("\r\n");

	// ���ڻ�����ʾ��־

	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;

	// ��ʽ����ǰʱ��


	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);

	//��ȡ�༭�����һ������

	m_event.SetSel(lastLine + 1, lastLine + 2, 0);

	//ѡ��༭�����һ��

	m_event.ReplaceSel(string);                                                             //�滻��ѡ��һ�е�����

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
