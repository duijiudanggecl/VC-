
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"
#include "afxcmn.h"




class CClientSocket;

// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	CButton m_ConPC;
	CString m_DataSend;


	bool m_connect;

	CClientSocket* pSock;                        // �ͻ����׽���ָ�����

	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);

	//�ַ�ת������

public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//��ֹ����enter��escʱ�˳�����

	afx_msg void OnBnClickedConcect();
	afx_msg void OnBnClickedSend();
	afx_msg void OnEnChangeDatareceive();

	void RecvData(CClientSocket* pSocket);

	void UpdateEvent(CString str);

	CEdit m_event;


	CIPAddressCtrl m_ServerIP;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
