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
	// ��ȡϵͳ��ǰʱ��
	//str += _T("\r\n");
	// ���ڻ�����ʾ��־
	//string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;
	// TODO:  �ڴ����ר�ô����/����û���

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

	//����Э��ͷ

	if (Send(lpBuff, nlen) == SOCKET_ERROR)

	{

		AfxMessageBox(_T("���ʹ���"));

		return FALSE;

	}

	return  TRUE;

}
