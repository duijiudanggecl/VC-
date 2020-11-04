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

	// 重写接收函数，通过类向导生成

	BOOL SendMSG(LPSTR lpBuff, int nlen);

	// 发送函数，用于发送数据给服务器

};

