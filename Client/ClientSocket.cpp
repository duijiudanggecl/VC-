#include "stdafx.h"
#include "ClientSocket.h"
#include  "Client.h"
#include  "ClientDlg.h"


CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}






void CClientSocket::OnReceive(int nErrorCode)

{
	 
	CString str;
	CString string;
	CTime time = CTime::GetCurrentTime();
	// 获取系统当前时间
	//str += _T("\r\n");
	// 用于换行显示日志
	//string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;
	// TODO:  在此添加专用代码和/或调用基类

	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char) * 1024);
	UCHAR leng = 0;
	leng = Receive(pData, 1024, 0);
	str = pData;
	//str += _T("\r\n");
	//str += string;

	//IDC_LIST1
	//((CClientDlg*)theApp.GetMainWnd())->SetDlgItemTextW(IDC_MESGE, str);

//	((CClientDlg*)theApp.GetMainWnd()))->SetCurSel(IDC_MESGE,1);

((CClientDlg*)theApp.GetMainWnd())->UpdateEvent(str);


//	m_pDlg->UpdateEvent(str);

	delete pData;

	pData = NULL;


	//m_pDlg->RecvData(str);
	
	//m_pDlg->RecvData(this);

	CSocket::OnReceive(nErrorCode);


}



BOOL CClientSocket::SendMSG(LPSTR lpBuff, int nlen)

{

	//生成协议头

	if (Send(lpBuff, nlen) == SOCKET_ERROR)

	{

		AfxMessageBox(_T("发送错误！"));

		return FALSE;

	}

	return  TRUE;

}
