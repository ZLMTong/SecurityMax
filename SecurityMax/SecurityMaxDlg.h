
// SecurityMaxDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MyInterface.h"
#define ONMYKEY 0xa001

// CSecurityMaxDlg �Ի���
class CSecurityMaxDlg : public CDialogEx
{
// ����
public:
	CSecurityMaxDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECURITYMAX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	CMyInterface m_TabInterface;
	BOOL m_IsWindowHide = TRUE;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

	afx_msg void OnShutdown();
	afx_msg void OnRebot();
	afx_msg void On32779();
	afx_msg void OnSleep();
	afx_msg void OnSleepOff();
	afx_msg void On32782();
};
