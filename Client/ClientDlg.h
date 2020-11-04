
// ClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"
#include "afxcmn.h"




class CClientSocket;

// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	CButton m_ConPC;
	CString m_DataSend;


	bool m_connect;

	CClientSocket* pSock;                        // 客户端套接字指针对象

	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);

	//字符转换函数

public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//防止按下enter、esc时退出程序

	afx_msg void OnBnClickedConcect();
	afx_msg void OnBnClickedSend();
	afx_msg void OnEnChangeDatareceive();

	void RecvData(CClientSocket* pSocket);

	void UpdateEvent(CString str);

	CEdit m_event;


	CIPAddressCtrl m_ServerIP;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
