#pragma once
//#include "ClientDlg.h"
#include "afxsock.h"



class CClientDlg;

class CClientSocket :
	public CSocket
{
public:
	CClientSocket();
	~CClientSocket();

	CClientDlg*  m_pDlg;

	virtual void OnReceive(int nErrorCode);

	// ��д���պ�����ͨ����������

	BOOL SendMSG(LPSTR lpBuff, int nlen);

	// ���ͺ��������ڷ������ݸ�������

};

