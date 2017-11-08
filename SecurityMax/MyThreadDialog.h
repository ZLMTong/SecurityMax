#pragma once
#include "afxcmn.h"


// CMyThreadDialog �Ի���

class CMyThreadDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyThreadDialog)

public:
	CMyThreadDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CMyThreadDialog(DWORD processID, CWnd* pParent = NULL);
	virtual ~CMyThreadDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ThreadList;
	DWORD m_processID;
	CString m_stcInfo;		//������
	DWORD m_dwProcId;		//����ID
	bool GetThreadInfo(DWORD dwProceId);
	virtual BOOL OnInitDialog();
};
